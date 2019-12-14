#include "State.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <list>

#include "Powerup.h"
#include "Box.h"
#include "Bomb.h"
#include "Fire.h"
#include "Player.h"
#include "PC.h"
#include "Menu_button.h"
#include "NPC.h"
#include <stdlib.h>     
#include <time.h>       

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <tuple>
#include <fstream>

/*
 * GAME_STATE
 *
*/


//TODO: is_playing should be initialised as false when state_handler is implemented fully.
Game_state::Game_state(): State("Game_state"),
			  current_round{0}, players{}, alive_players{}, bombs{}, fires{}, wooden_boxes{}, solid_boxes{}, is_playing{true}
    {
        fire_texture.loadFromFile("textures/fire_texture.png");
        player1_texture.loadFromFile("textures/Player1_left.png");
        player2_texture.loadFromFile("textures/player2_texture.png");
        player3_texture.loadFromFile("textures/player3_texture.png");
        player4_texture.loadFromFile("textures/player4_texture.png");
        solid_box_texture.loadFromFile("textures/solid_texture.png");
        wooden_box_texture.loadFromFile("textures/wooden_texture.png");
        bomb_texture.loadFromFile("textures/bomb_texture.png");
        push_texture.loadFromFile("textures/push_texture.png");
        extra_bomb_texture.loadFromFile("textures/extra_bomb_texture.png");
        speed_texture.loadFromFile("textures/speed_texture.png");
    	bigger_blast_texture.loadFromFile("textures/bigger_blast_texture.png");
    }

void Game_state::update(sf::Mouse& mouse, sf::Keyboard& keyboard)
{
    user_input_handler(mouse, keyboard);

    fires.remove_if([](Fire* fire)
        {
            if (fire->is_extinguished())
            {
         //       delete fire;
                return true;
            }
            return false;
        });

    bombs.remove_if([this](Bomb* bomb)
        {
            if (bomb->is_blasted())
            {
                bomb->spawn_fire(wooden_boxes, solid_boxes, fires, fire_texture);
                //delete bomb;
                return true;
            }
            return false;
        });
       
    if (!is_playing)
    {
        // TODO: All clocks still run (both here and in player) so pausing will
        // have unintended consequenses - exidental features. This problem has
        // no trivaial solutions since sf::Clock has no pause function.
        return;
    }

    for (Player* player : alive_players)
    {
        if (player->request_to_drop_bomb())
        {
            bombs.push_back(player->create_bomb(bomb_texture));
        }
	Pc* ptr1 = dynamic_cast<Pc*>(player);
	Npc* ptr2 = dynamic_cast<Npc*>(player);
	if (ptr1 != nullptr)
	{
	    ptr1->update(keyboard);
	}
	else
	{
	    ptr2->update(alive_players, bombs, fires, powerups, wooden_boxes, solid_boxes);
	}
    }

    for (Bomb* bomb : bombs)
    {
    	bomb->update();
    }


    check_collisions();
    
    wooden_boxes.remove_if(
	[this](Wooden_box* wooden_box)
        {
	    if (!wooden_box->is_dead())
	    {
	        return false;
	    }
	    if (rand() % 2 + 1 == 2)
	    {
		int rand_int = rand() % 4 + 1; 
	        if (rand_int == 1)
	        {
		    powerups.push_back(new Speed(wooden_box->get_position(), speed_texture));
		}
	        else if (rand_int == 2)
	        {
		    powerups.push_back(new Bigger_blast(wooden_box->get_position(), bigger_blast_texture));
		}
	        else if (rand_int == 3)
	        {
		    powerups.push_back(new Extra_bomb(wooden_box->get_position(), extra_bomb_texture));
		}
	        else  //rand_int == 4.
	        {
		    powerups.push_back(new Push(wooden_box->get_position(), push_texture));
		}
	    }
	    return true;
	});

    
    alive_players.remove_if([this](Player* player)
        {
            return player->is_dead();  
        });
    

    if (is_round_over())
    {
        new_round();
        if (is_game_over())
        {
            end_game();
        }
    }
}

void Game_state::check_collisions()
{   
    for (Player* player : alive_players)
    {
        for (Bomb* bomb : bombs)
            if (player->hitbox().intersects(bomb->hitbox()))
            {
                bomb->apply_on_hit_effect(player);
                player->apply_on_hit_effect(bomb);
            }
        for (Fire* fire : fires)
        {
            if (player->hitbox().intersects(fire->hitbox()))
            {
                fire->apply_on_hit_effect(player);
            }
        }
        for (Wooden_box* wooden_box : wooden_boxes)
        {
            if (player->hitbox().intersects(wooden_box->hitbox()))
            {
                wooden_box->apply_on_hit_effect(player);
            }
        }
        for (Solid_box* solid_box : solid_boxes)
        {
            if (player->hitbox().intersects(solid_box->hitbox()))
            {
                solid_box->apply_on_hit_effect(player);
            }
        }
	powerups.remove_if([player](Powerup* powerup)
	    {
		if (player->hitbox().intersects(powerup->hitbox()))
		{
		    powerup->apply_on_hit_effect(player);
		    delete powerup;
		    return true;
		}
		return false;
	    });
    }
    for (Bomb* bomb : bombs)
    {
        for (Bomb* bomb2 : bombs)
        {
            if (bomb->hitbox().intersects(bomb2->hitbox()) && bomb != bomb2)
            {
                bomb->apply_on_hit_effect(bomb2);
                bomb2->apply_on_hit_effect(bomb);
                bomb->undo_last_move();
                bomb2->undo_last_move();
            }
        }
        for (Wooden_box* wooden_box : wooden_boxes)
        {
            if (bomb->hitbox().intersects(wooden_box->hitbox()))
            {
                bomb->apply_on_hit_effect(wooden_box);
                wooden_box->apply_on_hit_effect(bomb);
            }
        }
        for (Solid_box* solid_box : solid_boxes)
        {
            if (bomb->hitbox().intersects(solid_box->hitbox()))
            {
                bomb->apply_on_hit_effect(solid_box);
                solid_box->apply_on_hit_effect(bomb);
            }
        }
    }
    for (Fire* fire : fires)
    {
        for (Wooden_box* wooden_box : wooden_boxes)
        {
            if (fire->hitbox().intersects(wooden_box->hitbox()))
            {
                fire->apply_on_hit_effect(wooden_box);
                wooden_box->apply_on_hit_effect(fire);
		//Should fire detonate other bombs?
            }
        }
    }   
}


void Game_state::draw(sf::RenderWindow& window)
{
    for (Player* player : alive_players)
    {
        if (!player->is_dead())
        {
            window.draw(player->get_drawable());
        }
    }
    for (Wooden_box* wooden_box : wooden_boxes)
        window.draw(wooden_box->get_drawable());
    for (Solid_box* solid_box : solid_boxes)
        window.draw(solid_box->get_drawable());
    for (Fire* fire : fires)
        window.draw(fire->get_drawable());
    for (Bomb* bomb : bombs)
        window.draw(bomb->get_drawable());
    for (Powerup* powerup : powerups)
        window.draw(powerup->get_drawable());

    //for (Menu_button* menu_button : menu_buttons)
    //    window.draw(menu_button->get_drawable());
}


void Game_state::user_input_handler(sf::Mouse& mouse, sf::Keyboard& keyboard)
{
    /*
    if (mouse.isButtonPressed(sf::Mouse::Left)
    {
        if (quit_button->click(mouse))
        {
            current_state_string = "menu_state";
            end_game();
        }
        if (pause_button->click(mouse))
        {
            is_playing = !is_playing
        }
    }
    */
}

void Game_state::new_round()
{
    for (Player* player : players)
    {
        if (!player->is_dead())
        {
            player->increase_score(100);
        }
        player->new_round();
    }
    current_round += 1;
    
    wooden_boxes.clear(); //This prolly causes memory leaks...
    powerups.clear();
    alive_players = players;
    bombs.clear();
    fires.clear();
    initialize_boxes();

    round_timer.restart();

}

sf::Texture& Game_state::get_texture(sf::Texture& t1, sf::Texture& t2, sf::Texture& t3, sf::Texture& t4, int idx) 
{
    switch (idx)
    {
        case 0: return t1;
        case 1: return t2;
        case 2: return t3;
        case 3: return t4;
    }
}

void Game_state::new_game(int PC, int NPC1, int NPC2, int NPC3)
{  
    sf::Vector2f offset{250,50};

    std::vector<sf::Vector2f> positions{sf::Vector2f(50,50), sf::Vector2f(650,50), sf::Vector2f(650,550), sf::Vector2f(50,550)}; //Start_pos.
    std::vector<std::string> names{"Player 1", "Player 2", "Player 3", "Player 4"};
    std::vector<sf::Keyboard::Key> player1_buttons{sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::S, sf::Keyboard::W, sf::Keyboard::Q};
    std::vector<sf::Keyboard::Key> player2_buttons{sf::Keyboard::Numpad1, sf::Keyboard::Numpad3, sf::Keyboard::Numpad2, sf::Keyboard::Numpad5, sf::Keyboard::Numpad4};
    std::vector<sf::Keyboard::Key> player3_buttons{sf::Keyboard::Num0, sf::Keyboard::Num1, sf::Keyboard::Num2, sf::Keyboard::Num3, sf::Keyboard::Num4};
    std::vector<sf::Keyboard::Key> player4_buttons{sf::Keyboard::Num5, sf::Keyboard::Num6, sf::Keyboard::Num7, sf::Keyboard::Num8, sf::Keyboard::Num9};
    std::vector<std::vector<sf::Keyboard::Key>> buttons{player1_buttons, player2_buttons, player3_buttons, player4_buttons};
    std::vector<sf::Texture> textures{player1_texture, player2_texture, player3_texture, player4_texture};
    
    PC = 4;
    NPC1 = 0;
    NPC2 = 0;
    NPC3 = 0;
    
    int initilized{0};                  
    for (int i{0}; i < PC; i++)
    {
	sf::Texture& tet = get_texture(player1_texture, player2_texture, player3_texture, player4_texture, initilized);
        players.push_back(new Pc(positions[initilized] + offset, tet, false, 3, 2, 2, 3, names[initilized],
				 buttons[initilized][0], buttons[initilized][1], buttons[initilized][2], buttons[initilized][3], buttons[initilized][4]));
        initilized++;
    }
    for (int i{0}; i < NPC1; i++)
    {
	sf::Texture& tet = get_texture(player1_texture, player2_texture, player3_texture, player4_texture, initilized);
        players.push_back(new Npc(positions[initilized] + offset, tet, false, 3, 2, 2, 3, names[initilized]));
        initilized++;
    }
    for (int i{0}; i < NPC2; i++)
    {
	sf::Texture& tet = get_texture(player1_texture, player2_texture, player3_texture, player4_texture, initilized);
        players.push_back(new Npc(positions[initilized] + offset, tet, false, 3, 6, 2, 6, names[initilized]));
        initilized++;
    }
    for (int i{0}; i < NPC3; i++)
    {
	sf::Texture& tet = get_texture(player1_texture, player2_texture, player3_texture, player4_texture, initilized);
        players.push_back(new Npc(positions[initilized] + offset, tet, false, 3, 2, 2, 6, names[initilized]));
        initilized++;
    }
    
    alive_players = players;
    is_playing = true;
    initialize_boxes();
    round_timer.restart();
    current_round = 0;
}

void Game_state::initialize_boxes()
{
    std::ifstream maptext;
    maptext.open("initmatrix.txt");
    std::vector<std::vector<int>> mat;
    std::vector<int> row;
    int val;
    for(uint i{0}; i < 13; ++i)
    {
        row.clear();
        for(uint j{0}; j < 15; ++j)
        {
            maptext >> val;
            row.push_back(val);
        }
        mat.push_back(row);
    }

    for(int r{0}; r < 13; r++)
    {
        for(int c{0}; c < 15; c++)
        {
            switch(mat[r][c])
            {
                case 0 :
                    break;
                case 1 :
                    solid_boxes.push_back(new Solid_box(sf::Vector2f(c*50, r*50) + offset, solid_box_texture));
                    break;
                case 2 :
                    wooden_boxes.push_back(new Wooden_box(sf::Vector2f(c*50, r*50) + offset, wooden_box_texture));
                default :
                    break;
            }
        }
    }
}

void Game_state::end_game()
{
    /*
     * TODO: delete relevant objects
     * run the function that passes players to End_screen
     * Change current state to End_screen
     * set is_playing to false.
    */
}

bool Game_state::is_round_over()
{
    if (is_time_up())
    {
        return true;
    }

    int alive_players_count = std::count_if(players.begin(), players.end(),
            [] (Player* p) {return !p->is_dead();});

    //This works even if only one player is playing the game. In english,
    //if someone is dead and no more than one player is alive return true.
    if (players.size() > alive_players_count && alive_players_count <= 1)
    {
        return true;
    }
    return false;
}

bool Game_state::is_game_over()
{
    return is_round_over() && current_round > 2;
}

bool Game_state::is_time_up()
{
    return round_timer.getElapsedTime().asSeconds() > 180;
}


/*
 * MENU_STATE
 *
*/


void Menu_state::update(sf::Mouse& mouse, sf::Keyboard& keyboard)
{
    user_input_handler(mouse, keyboard);
}

void Menu_state::user_input_handler(sf::Mouse& mouse, sf::Keyboard&)
{
    //check the collisions with menu_buttons
    /*
    if (mouse.isButtonPressed(sf::Mouse::Left)
    {
        PC_button->click(mouse);
        NPC1_button->click(mouse);
        NPC2_button->click(mouse);
        NPC3_button->click(mouse);

        if (start_button->click(mouse))
        {
            nr_players = PC->get_value() +
                NPC1->get_value() +
                NPC2->get_value() +
                NPC3->get_value();

            if (nr_players <= 4 && nr_players != 0)
            {
                game_state->create_game(PC->get_value(),
                                    NPC1->get_value(),
                                    NPC2->get_value(),
                                    NPC3->get_value());
            }
            else
            {
                //not valid game message
            }
        }
    }
    */
}

void Menu_state::draw(sf::RenderWindow& window)
{
    /*
    for (Menu_button* menu_button : menu_buttons)
    {
        window.draw(menu_button->get_drawable());
    }
    */
    //we need to somewhere give the buttons a position. Maybe that can be done here based on the size of window. We might add a scaling too.
    //And perhaps draw some fancy background
}

struct PlayerComparator
{
	// Compare 2 Player objects using points
  bool operator ()(Player* & player1, Player* & player2)
	{
	  if(player1->get_score() == player2->get_score())
	    return player1->get_score() < player2->get_score();
	  return player1->get_score() < player2->get_score();
 
	}
};


End_screen::End_screen(sf::Texture s, std::list<Player*> list)
  :State("end_screen"), sprite{s}, list_of_Player{list},
   pos{50,50}, end_button{pos, sprite}
{

  list_of_Player.sort(PlayerComparator());
  
}

void End_screen::Draw(sf::RenderWindow& window)
{
    int number{1};  
    int ycorrd{70};
        
    sf::Font font;    
    if (!font.loadFromFile("arial.ttf"));

 for (Player* player : list_of_Player)
    {
      
      std::ostringstream info;
      info << number << ".  " << player->get_name() << "  Points: " << player->get_score();
    
    sf::Text text(info.str(), font, 50);
    text.setPosition(70,ycorrd);
    text.setColor(sf::Color::Red);
    
    window.draw(text);
    
    ycorrd= ycorrd + 70;    
    number= number + 1;

    }


 end_button.draw(window);
}

