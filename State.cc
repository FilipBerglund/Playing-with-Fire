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

/*
 * GAME_STATE
 *
*/


//TODO: is_playing should be initialised as false when state_handler is implemented fully.
Game_state::Game_state(): State("Game_state"),
    current_round{0}, players{}, bombs{}, fires{}, wooden_boxes{}, solid_boxes{}, is_playing{true}
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


    if (!is_playing)
    {
        // TODO: All clocks still run (both here and in player) so pausing will
        // have unintended consequenses - exidental features. This problem has
        // no trivaial solutions since sf::Clock has no pause function.
        return;
    }

    for (Player* player : players)
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
	    ptr2->update(players, bombs, fires, powerups, wooden_boxes, solid_boxes);
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

    //TODO: Add remove_if for bombs and fires. The remove_if of bombs should also spawn fire.
    //Note that powerups are removed in check_collisions().

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
    for (Player* player : players)
    {
        for (Bomb* bomb : bombs)
            if (player->hitbox().intersects(bomb->hitbox()))
            {
		    std::cout << "bomb" << std::endl;
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
                //add check if bomb1 == bomb
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
            }
        }
    }
}


void Game_state::draw(sf::RenderWindow& window)
{
    for (Player* player : players)
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
    //TODO: Add removal of powerups, wooden_boxes, bombs, fires
    //TODO: spawn Wooden_boxes
    round_timer.restart();

}

void Game_state::new_game(int PC, int NPC1, int NPC2, int NPC3)
{
    //initialize everything
   // Player* player = new Player(sf::Vector2f(300,300), player1_texture, 3, false, 3, 5, 2, 5);
    //players.push_back(player);
    Pc* pc = new Pc(sf::Vector2f(150,150), player1_texture, 3, false, 3, 2, 2, 5, "Pelle svanslös", sf::Keyboard::A,sf::Keyboard::D,sf::Keyboard::S,sf::Keyboard::W,sf::Keyboard::Q);
    players.push_back(pc);
/*
    Npc* npc1 = new Npc(sf::Vector2f(150,250), player1_texture, 3, false, 3, 2, 2, 5, "Pelle svanslös");
    players.push_back(npc1);

    Npc* npc2 = new Npc(sf::Vector2f(200,250), player1_texture, 3, false, 3, 2, 2, 5, "Pelle svanslös");
    players.push_back(npc2);
    
    Npc* npc3 = new Npc(sf::Vector2f(250,250), player1_texture, 3, false, 3, 2, 2, 5, "Pelle svanslös");
    players.push_back(npc3);
    
    Npc* npc4 = new Npc(sf::Vector2f(300,250), player1_texture, 3, false, 3, 2, 2, 5, "Pelle svanslös");
    players.push_back(npc4);
    */

    powerups.push_back(new Speed(sf::Vector2f(600,250), speed_texture));
    powerups.push_back(new Bigger_blast(sf::Vector2f(650,250), bigger_blast_texture));
    powerups.push_back(new Extra_bomb(sf::Vector2f(600,350), extra_bomb_texture));
    powerups.push_back(new Push(sf::Vector2f(600,450), push_texture));
    
	
    
    
    
   for (int i = 2; i < 19; i++)
   { 
    	solid_boxes.push_back(new Solid_box(sf::Vector2f(i*50, 100), solid_box_texture));
        solid_boxes.push_back(new Solid_box(sf::Vector2f(i*50, 700), solid_box_texture));
   }
   for (int i = 2; i < 19; i++)
   { 
    	solid_boxes.push_back(new Solid_box(sf::Vector2f(100, i*50), solid_box_texture));
    	solid_boxes.push_back(new Solid_box(sf::Vector2f(900, i*50), solid_box_texture));
   }
   for (int i = 2; i < 10; i++)
   { 
   	for (int j = 2; j < 10; j++)
	{ 
		solid_boxes.push_back(new Solid_box(sf::Vector2f(i*100, j*100), solid_box_texture));
	}
   }

    round_timer.restart();
    is_playing = true;
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

