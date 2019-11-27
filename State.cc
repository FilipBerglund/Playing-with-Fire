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


#include <iostream>
#include <string>
/*
 * GAME_STATE
 *
*/


Game_state::Game_state(): State("Game_state"),
    current_round{0}, players{}, bombs{}, fires{}, wooden_boxes{}, solid_boxes{}, is_playing{true}
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
    }

void Game_state::update(sf::Mouse& mouse, sf::Keyboard& keyboard)
{
    user_input_handler(mouse, keyboard);
    check_collisions();


    if (!is_playing)
    {
        //All clocks still run (both here and in player) so pausing will
        //have unintended consequenses - exidental features.
        return;
    }

    for (Player* player : players)
    {
        player->update(keyboard);

        if (player->request_to_drop_bomb())
        {
            bombs.push_back(player->create_bomb(bomb_texture));
        }
    }

    wooden_boxes.remove_if(
            [](Wooden_box* wooden_box){return wooden_box->is_dead();});


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
                std::cout << "collision" << std::endl;
            }
        }
        for (Solid_box* solid_box : solid_boxes)
        {
            if (player->hitbox().intersects(solid_box->hitbox()))
            {
                solid_box->apply_on_hit_effect(player);
            }
        }
        for (Powerup* powerup : powerups)
        {
            if (player->hitbox().intersects(powerup->hitbox()))
            {
                powerup->apply_on_hit_effect(player);
                powerups.remove(powerup);
            }
        }
    }
    for (Bomb* bomb : bombs)
    {
        for (Bomb* bomb2 : bombs)
        {
            if (bomb->hitbox().intersects(bomb2->hitbox()))
                //add check if bomb1 == bomb
            {
                bomb->apply_on_hit_effect(bomb2);
                bomb2->apply_on_hit_effect(bomb);
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
    for (Player* player : players)
    {
        player->update(keyboard);
    }

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
    //remove powerups, wooden_boxes, bombs, fires
    //spawn Wooden_boxes
    round_timer.restart();

}

void Game_state::new_game(int PC, int NPC1, int NPC2, int NPC3)
{
    //initialize everything
   // Player* player = new Player(sf::Vector2f(300,300), player1_texture, 3, false, 3, 5, 2, 5);
    //players.push_back(player);
    Pc* pc = new Pc(sf::Vector2f(300,300), player1_texture, 3, false, 3, 1, 2, 5, sf::Keyboard::A,sf::Keyboard::D,sf::Keyboard::S,sf::Keyboard::W,sf::Keyboard::J);
    players.push_back(pc);
    
    wooden_boxes.push_back(new Wooden_box(sf::Vector2f(800, 300), wooden_box_texture));

    round_timer.restart();
    is_playing = true;
}

void Game_state::end_game()
{
    //delete relevant objects
    //run the function that passes players to End_screen
    //Change current state to End_screen
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
