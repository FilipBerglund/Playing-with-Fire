#include "State.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <list>
#include "Powerup.h"
#include "Box.h"
#include "Bomb.h"
#include "Fire.h"
#include "PC.h"
#include "Menu_button.h"
#include "NPC1.h"
#include "NPC2.h"
#include "NPC3.h"
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
Game_state::Game_state():
    State("Game_state"),
    round_timer{},
    current_round{0},
    round_length{},
    number_of_rounds{},
    is_playing{true},
    players{},
    alive_players{},
    bombs{},
    fires{},
    powerups{},
    wooden_boxes{},
    solid_boxes{},
    offset{},

    player1_texture{},
    player2_texture{},
    player3_texture{},
    player4_texture{},
    player_textures{},
    fire_texture{},
    solid_box_texture{},
    wooden_box_texture{},
    bomb_texture{},
    push_texture{},
    extra_bomb_texture{},
    bigger_blast_texture{},
    speed_texture{},
    quit_button_texture{},
    back_button_texture{},

    state_bg{},
    state_bg_texture{},

    explosion_buffer{},
    explosion_sound{},

    quit_button{},
    back_button{},

    player_positions{},
    player_names{},
    player_buttons{}
    {
        std::uniform_int_distribution<int> dist{0, 99};
        load_game_data();
        load_player_data();
        load_textures();
        load_sounds();

        state_bg.setTexture(state_bg_texture);
        state_bg.setPosition(sf::Vector2f(0,0));

        float coordx{10};
        float d{quit_button_texture.getSize().x + 5.f};
        quit_button = new Bool_button(sf::Vector2f(coordx+0*d,630), quit_button_texture);
        back_button = new Bool_button(sf::Vector2f(coordx+1*d,630), back_button_texture);
    }

void Game_state::destroy_nonplayer_objects()
{   
    bombs.remove_if([this](Bomb* bomb)
    {
        delete bomb;
        return true;
    });
    fires.remove_if([this](Fire* fire)
        {
            delete fire;
            return true;
        });

    powerups.remove_if([this](Powerup* powerup)
        {
            delete powerup;
            return true;
        });

    solid_boxes.remove_if([this](Solid_box* solid_box)
        {
            delete solid_box;
            return true;
        });

    wooden_boxes.remove_if([this](Wooden_box* wooden_box)
        {
            delete wooden_box;
            return true;
        });
}

void Game_state::destroy_players()
{
    players.remove_if([this](Player* player)
        {
            delete player;
            return true;
        });

    alive_players.remove_if([this](Player* player)
        {
            delete player;
            return true;
        }); 
}


Game_state::~Game_state()
{
    destroy_nonplayer_objects();
    destroy_players();
}

void Game_state::update(sf::Mouse& mouse, sf::Keyboard& keyboard,
    Game_state* game_state, Menu_state* menu_state,
    End_screen* end_screen, State** current_state, sf::RenderWindow& window)
{
    user_input_handler(mouse, keyboard, game_state, menu_state, end_screen, current_state, window);
    check_collisions();

    fires.remove_if([this](Fire* fire)
        {
            if (fire->is_extinguished())
            {
                delete fire;
                return true;
            }
            return false;
        });

    bombs.remove_if([this](Bomb* bomb)
        {
            if (bomb->is_blasted())
            {
                explosion_sound.play();
                bomb->spawn_fire(wooden_boxes, solid_boxes, fires, fire_texture);
                delete bomb;
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
        Pc* pc = dynamic_cast<Pc*>(player);
        Npc* npc = dynamic_cast<Npc*>(player);
        if (pc != nullptr)
        {
            pc->update(keyboard);
        }
        else
        {
            npc->update(alive_players, bombs, fires, powerups, wooden_boxes, solid_boxes);
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
        int rand_int2 = dist(rd) % 2 + 1;
        if (rand_int2 == 2)
        {
            int rand_int = dist(rd) % 4 + 1;
            if (rand_int == 1)
            {
                powerups.push_back(new Speed(wooden_box->get_position(),
                                             speed_texture));
            }
            else if (rand_int == 2)
            {
                powerups.push_back(new Bigger_blast(wooden_box->get_position(),
                                                    bigger_blast_texture));
            }
            else if (rand_int == 3)
            {
                powerups.push_back(new Extra_bomb(wooden_box->get_position(),
                                                  extra_bomb_texture));
            }
            else  //rand_int == 4.
            {
                powerups.push_back(new Push(wooden_box->get_position(),
                                            push_texture));
            }
            delete wooden_box;
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
            end_game(current_state, end_screen);
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
            if (abs(fire->get_position().x - player->get_position().x) < 40 &&
		abs(fire->get_position().y - player->get_position().y) < 40)
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
            }
        }
        bombs.remove_if([fire,this](Bomb* bomb)
        {
            if (bomb->hitbox().intersects(fire->hitbox()))
            {
                explosion_sound.play();
                bomb->spawn_fire(wooden_boxes, solid_boxes, fires, fire_texture);
                delete bomb;
                return true;
            }
            return false;
        });

    }
}


void Game_state::draw(sf::RenderWindow& window)
{
    window.draw(state_bg);

    //Round counter
    sf::Font font;
    font.loadFromFile("res/arial.ttf");
    std::ostringstream info;
    info << "ROUND: " << current_round + 1;
    sf::Text text0(info.str(), font, 40);
    text0.setPosition(10,10);
    text0.setFillColor(sf::Color::Black);
    window.draw(text0);

    //Timer
    std::ostringstream roundtimerinfo;
     roundtimerinfo << "Time remaining: "
        << (int)(round_length - round_timer.getElapsedTime().asSeconds());
    sf::Text text1(roundtimerinfo.str(), font, 20);
    text1.setPosition(10,window.getSize().y - 30);
    text1.setFillColor(sf::Color::Black);
    window.draw(text1);

    int number{1};
    int ycorrd{100};

    for (Player* player :  players)
    {
        std::ostringstream name_info;
        name_info << player->get_name();
        sf::Text text0(name_info.str(), font, 20);

        std::ostringstream score_info;
        score_info << "Points: " << player->get_score();
        sf::Text text1(score_info.str(), font, 20);

        std::ostringstream health_info;
        health_info << "Hp: " << player->get_health();
        sf::Text text2(health_info.str(), font, 20);

        text0.setPosition(10, ycorrd);
        text0.setFillColor(sf::Color::Black);
        text1.setPosition(130, ycorrd);
        text1.setFillColor(sf::Color::Black);
        text2.setPosition(250, ycorrd);
        text2.setFillColor(sf::Color::Red);

        window.draw(text0);
        window.draw(text1);
        window.draw(text2);

        ycorrd = ycorrd + 30;
        number = number + 1;
    }

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
    {
        window.draw(bomb->get_drawable());
        bomb->draw(window, font);
    }
    for (Powerup* powerup : powerups)
        window.draw(powerup->get_drawable());

    quit_button->draw(window);
    back_button->draw(window);
}


void Game_state::user_input_handler(sf::Mouse& mouse, sf::Keyboard&,
                                    Game_state*, Menu_state* menu_state,
                                    End_screen*, State** current_state,
                                    sf::RenderWindow& window)
{
    if (mouse.isButtonPressed(sf::Mouse::Left))
    {
        if (quit_button->click(mouse,window))
        {
            window.close();
        }
        if (back_button->click(mouse,window))
        {
            *current_state = menu_state;
        }
    }
}

void Game_state::new_round()
{
    for (Player* player : players)
    {
	int shareholders{(int)alive_players.size()};
	int share{120/shareholders};
	if (!player->is_dead())
        {
            player->increase_score(share);
        }
        player->new_round();
    }
    
    destroy_nonplayer_objects();
    alive_players = players;
    initialize_map();
    round_timer.restart();
    current_round += 1;
}

sf::Texture& Game_state::get_texture(sf::Texture& t1, sf::Texture& t2, sf::Texture& t3, sf::Texture& t4, int idx)
{
    switch (idx)
    {
        case 0:  return t1;
        case 1:  return t2;
        case 2:  return t3;
        default: return t4;
    }
}

void Game_state::new_game(int PC, int NPC1, int NPC2, int NPC3)
{
    destroy_players();  //Removes the players from the previous game.
    new_round();
    is_playing = true;
    current_round = 0;

    int initilized{0};
    for (int i{0}; i < PC; i++)
    {
        sf::Texture& tet = get_texture(
                player1_texture,
                player2_texture,
                player3_texture,
                player4_texture,
                initilized);
        players.push_back(new Pc(player_positions[initilized], tet, false,
            3, 1, 2, 3, player_names[initilized],
            player_buttons[initilized][0],
            player_buttons[initilized][1],
            player_buttons[initilized][2],
            player_buttons[initilized][3],
            player_buttons[initilized][4]));
        initilized++;
    }
    for (int i{0}; i < NPC1; i++)
    {
        sf::Texture& tet = get_texture(
                player1_texture,
                player2_texture,
                player3_texture,
                player4_texture,
                initilized);
        players.push_back(new Npc1(player_positions[initilized], tet,
                   player_names[initilized]));
        initilized++;
    }
    for (int i{0}; i < NPC2; i++)
    {
        sf::Texture& tet = get_texture(
                player1_texture,
                player2_texture,
                player3_texture,
                player4_texture,
                initilized);
        players.push_back(new Npc2(player_positions[initilized], tet,
                   player_names[initilized]));
        initilized++;
    }
    for (int i{0}; i < NPC3; i++)
    {
        sf::Texture& tet = get_texture(
                player1_texture,
                player2_texture,
                player3_texture,
                player4_texture,
                initilized);
        players.push_back(new Npc3(player_positions[initilized], tet,
                   player_names[initilized]));
        initilized++;
    }

    alive_players = players;
}

void Game_state::initialize_map()
{
    std::ifstream maptext;
    maptext.open("res/initmatrix.txt");

    int xpos;
    int ypos;
    maptext >> xpos;
    maptext >> ypos;
    offset = sf::Vector2f(xpos,ypos);

    int rows;
    int cols;
    maptext >> rows;
    maptext >> cols;

    std::vector<std::vector<int>> mat;
    std::vector<int> row;
    int val;
    for(int i{0}; i < rows; ++i)
    {
        row.clear();
        for(int j{0}; j < cols; ++j)
        {
            maptext >> val;
            row.push_back(val);
        }
        mat.push_back(row);
    }

    for(int r{0}; r < rows; r++)
    {
        for(int c{0}; c < cols; c++)
        {
            switch(mat[r][c])
            {
                case 0 :
                    break;

                case 1 :
                    solid_boxes.push_back(new Solid_box(
                                sf::Vector2f(c*50, r*50) + offset,
                                solid_box_texture));
                    break;

                case 2 :
                    if (dist(rd) % 100 < 80)
                    {
                        wooden_boxes.push_back(new Wooden_box(
                                    sf::Vector2f(c*50, r*50) + offset,
                                    wooden_box_texture));
                    }
                    break;

                case 3 :
                    player_positions.push_back(sf::Vector2f(50*c,50*r)+offset);
                    break;

                default :
                    break;
            }
        }
    }
}

void Game_state::end_game(State** current_state, End_screen* end_screen)
{
    destroy_nonplayer_objects();
    end_screen->new_players(players);
    *current_state = end_screen;
}

bool Game_state::is_round_over() const
{
    if (is_time_up())
    {
        return true;
    }

    //This works even if only one player is playing the game. In english,
    //if someone is dead and no more than one player is alive return true.
    if (players.size() > alive_players.size() && alive_players.size() <= 1)
    {
        return true;
    }
    return false;
}

bool Game_state::is_game_over() const
{
    return current_round > number_of_rounds - 1;
}

bool Game_state::is_time_up() const
{
    return round_timer.getElapsedTime().asSeconds() > round_length;
}

void Game_state::load_textures()
{
    fire_texture.loadFromFile("textures/fire_texture.png");
    player1_texture.loadFromFile("textures/player1_texture.png");
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
    quit_button_texture.loadFromFile("textures/quit.png");
    back_button_texture.loadFromFile("textures/backbutton.png");
    state_bg_texture.loadFromFile("textures/statetexture.png");
}

void Game_state::load_game_data()
{
    std::ifstream in_stream;
    in_stream.open("res/game_data.txt");
    in_stream >> number_of_rounds;
    in_stream >> round_length;
    in_stream.close();
}

void Game_state::load_player_data()
{
    std::ifstream in_stream;
    in_stream.open("res/player_data.txt");
    std::string name;
    while(std::getline(in_stream, name))
    {
        player_names.push_back(name);
    }
    in_stream.close();

    player_buttons.push_back(std::vector<sf::Keyboard::Key>{
        sf::Keyboard::A,
        sf::Keyboard::D,
        sf::Keyboard::S,
        sf::Keyboard::W,
        sf::Keyboard::Q});
    player_buttons.push_back(std::vector<sf::Keyboard::Key>{
        sf::Keyboard::Numpad1,
        sf::Keyboard::Numpad3,
        sf::Keyboard::Numpad2,
        sf::Keyboard::Numpad5,
        sf::Keyboard::Numpad4});
    player_buttons.push_back(std::vector<sf::Keyboard::Key>{
        sf::Keyboard::Left,
        sf::Keyboard::Right,
        sf::Keyboard::Down,
        sf::Keyboard::Up,
        sf::Keyboard::RControl});
    player_buttons.push_back(std::vector<sf::Keyboard::Key>{
        sf::Keyboard::J,
        sf::Keyboard::L,
        sf::Keyboard::K,
        sf::Keyboard::I,
        sf::Keyboard::U});
}

void Game_state::load_sounds()
{
    explosion_buffer.loadFromFile("res/explosion.wav");
    explosion_sound.setBuffer(explosion_buffer);
    explosion_sound.setPitch(0.2f);
    explosion_sound.setVolume(50.f);
}


/*
 * MENU_STATE
 *
*/

Menu_state::Menu_state(): State("Menu_state"),
    bg_texture{},
    background{},

    start_texture{},
    start_button{},

    pc_menu{},
    npc1_menu{},
    npc2_menu{},
    npc3_menu{},
    PC_button{},
    NPC1_button{},
    NPC2_button{},
    NPC3_button{}
{
    //Menu background
    bg_texture.loadFromFile("textures/background.png");
    background.setTexture(bg_texture);
    background.setPosition(sf::Vector2f(0,0));

    //Start button
    sf::Vector2f pos_start{610, 615};
    start_texture.loadFromFile("textures/start.png");
    start_button = new Bool_button(pos_start, start_texture);

    //Menu bar. IntRect:s are hard coded because they
    //are different sections of a png.
    pc_menu.loadFromFile("textures/Menu.png",   sf::IntRect(0,0,350,73));
    npc1_menu.loadFromFile("textures/Menu.png", sf::IntRect(0,74,350,75));
    npc2_menu.loadFromFile("textures/Menu1.png",sf::IntRect(0,74,350,75));
    npc3_menu.loadFromFile("textures/Menu2.png",sf::IntRect(0,74,350,75));

    int diff{75};
    int xpos{475};
    PC_button   = new Int_button(sf::Vector2f(xpos, 300 + 0*diff), pc_menu);
    NPC1_button = new Int_button(sf::Vector2f(xpos, 300 + 1*diff), npc1_menu);
    NPC2_button = new Int_button(sf::Vector2f(xpos, 300 + 2*diff), npc2_menu);
    NPC3_button = new Int_button(sf::Vector2f(xpos, 300 + 3*diff), npc3_menu);
}

void Menu_state::update(sf::Mouse& mouse, sf::Keyboard& keyboard,
                        Game_state* game_state, Menu_state* menu_state,
                        End_screen* end_screen, State** current_state ,sf::RenderWindow& window)
{
  user_input_handler(mouse, keyboard, game_state,
          menu_state, end_screen,
          current_state, window);
}

void Menu_state::user_input_handler(sf::Mouse& mouse, sf::Keyboard&,
    Game_state* game_state, Menu_state*,
    End_screen*, State** current_state, sf::RenderWindow& window)
{
    //check the collisions with menu_buttons
    if (mouse.isButtonPressed(sf::Mouse::Left))
    {
        PC_button->click(mouse, window);
        NPC1_button->click(mouse, window);
        NPC2_button->click(mouse, window);
        NPC3_button->click(mouse, window);
        if (start_button->click(mouse, window))
        {
            int nr_players = PC_button->get_value() +
                             NPC1_button->get_value() +
                             NPC2_button->get_value() +
                             NPC3_button->get_value();
            if (nr_players <= 4 && nr_players != 0)
            {
                game_state->new_game(PC_button->get_value(),
                                    NPC1_button->get_value(),
                                    NPC2_button->get_value(),
                                    NPC3_button->get_value());
                *current_state = game_state;
            }

        }
        else
        {
            //not valid game message
        }
    }
}

void Menu_state::draw(sf::RenderWindow& window)
{
     window.draw(background);
     start_button->draw(window);
     PC_button->draw(window);
     NPC1_button->draw(window);
     NPC2_button->draw(window);
     NPC3_button->draw(window);
}


/*
 * END_SCREEN
 *
*/

End_screen::~End_screen()
{
    list_of_Player.remove_if([this](Player* player)
    {
        delete player;
        return true;
    });
    delete end_button;
}

End_screen::End_screen() : State("end_screen"),
    list_of_Player{},
    pos{585,500},
    button_texture{},
    end_button{},
    end_background{},
    end_texture{}
{
    end_texture.loadFromFile("textures/endtexture.png");
    end_background.setTexture(end_texture);
    end_background.setPosition(sf::Vector2f(0,0));

    button_texture.loadFromFile("textures/okay.png");
    end_button = new Bool_button(pos, button_texture);
}

void End_screen::new_players(std::list<Player*> Players)
{
    list_of_Player = Players;
    list_of_Player.sort([](Player* player1, Player* player2)
    {
        return player1->get_score() > player2->get_score();
    });
}

void End_screen::update(sf::Mouse& mouse, sf::Keyboard& keyboard,
        Game_state* game_state, Menu_state* menu_state,
        End_screen* end_screen, State** current_state,
        sf::RenderWindow& window)
{
    user_input_handler(mouse, keyboard, game_state, menu_state,
            end_screen, current_state, window);
}

void End_screen::user_input_handler(sf::Mouse& mouse, sf::Keyboard&,
    Game_state*, Menu_state* menu_state,
    End_screen*, State** current_state, sf::RenderWindow& window)
{
    if (mouse.isButtonPressed(sf::Mouse::Left))
    {
        if (end_button->click(mouse, window))
        {
            list_of_Player.clear();
            *current_state = menu_state;
        }
        else
        {
            //not valid game message
        }
    }
}

void End_screen::draw(sf::RenderWindow& window)
{
    window.draw(end_background);
    int number{1};
    int ycorrd{175};

    sf::Font font;
    font.loadFromFile("res/arial.ttf");

    for (Player* player : list_of_Player)
    {
        std::ostringstream name_info;
        name_info << number << ".  " << player->get_name();
        sf::Text text0(name_info.str(), font, 50);
        std::ostringstream score_info;
        score_info << "Points: " << player->get_score();
        sf::Text text1(score_info.str(), font, 50);

        text0.setPosition((window.getSize().x / 2) - 400, ycorrd);
        text0.setFillColor(sf::Color::Yellow);
        text1.setPosition((window.getSize().x / 2) + 200, ycorrd);
        text1.setFillColor(sf::Color::Blue);

        window.draw(text0);
        window.draw(text1);

        ycorrd = ycorrd + 70;
        number = number + 1;
    }
    end_button->draw(window);
}
