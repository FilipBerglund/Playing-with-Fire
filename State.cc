#include "State.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <array>

#include "Player.h"
#include "Powerup.h"
#include "Box.h"


/*
 * GAME_STATE
 *
*/

using namespace sf
using namespace std

Game_state::Game_state(): State("Game_state"),
    current_round{0}, players{}, bombs{}, fires{}, wooden_boxes{}, solid_boxes{}
    {
        fire.loadFromFile("fire.png");
        player1.loadFromFile("player1.png");
        player2.loadFromFile("player2.png");
        player3.loadFromFile("player3.png");
        player4.loadFromFile("player4.png");
        solid_box.loadFromFile("solid_box.png");
        wooden_box.loadFromFile("wooden_box.png");
        bomb.loadFromFile("bomb.png");
        push.loadFromFile("push.png");
        extra_bomb.loadFromFile("extra_bomb.png");
        speed.loadFromFile("speed.png");
    }

void Game_state::update(sf::Mouse mouse, sf::Keyboard keyboard)
{
    user_input_handler(mouse, keyboard);
    for (Player& player : Players)
    {
        player.update(keyboard);

        if (player.dropbomb())
        {
            bombs.push_back(player.create_bomb());
        }
    }

    wooden_boxes.remove_if(
            [](Wooden_box wooden_box){return wooden_box.is_dead()});

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
    for (Player& player : players)
    {
        for (Bomb& bomb : bombs)
            if (player.hitbox().intersects(bomb.hitbox()))
            {
                bomb.apply_on_hit_effect(player);
                player.apply_on_hit_effect(bomb);
            }
        for (Fire& fire : fires)
        {
            if (player.hitbox().intersects(fire.hitbox()))
            {
                fire.apply_on_hit_effect(player);
            }
        }
        for (Box& box : boxes)
        {
            if (player.hitbox().intersects(box.hitbox()))
            {
                box.apply_on_hit_effect(player);
            }
        }
        for (Powerup& powerup : powerups)
        {
            if (player.hitbox().intersects(powerup.hitbox()))
            {
                powerup.apply_on_hit_effect(player);
                powerups.remove(powerup);
            }
        }
    }
    for (Bomb& bomb : bombs)
    {
        for (Bomb& bomb2 : bombs)
        {
            if (bomb.hitbox().intersects(bomb2.hitbox()))
                //add check if bomb1 == bomb
            {
                bomb.apply_on_hit_effect(bomb2);
                bomb2.apply_on_hit_effect(bomb);
            }
        }
        for (Box& box : boxes)
        {
            if (bomb.hitbox().intersects(box.hitbox()))
            {
                bomb.apply_on_hit_effect(box);
                box.apply_on_hit_effect(bomb);
            }
        }
    }
    for (Fire& fire : fires)
    {
        for (Box& box : boxes)
        {
            if (fire.hitbox().intersects(box.hitbox()))
            {
                fire.apply_on_hit_effect(box);
                box.apply_on_hit_effect(fire);
            }
        }
    }
}


void Game_state::draw(sf::Window& window)
{
    for (Player& player : players)
    {
        if (!player.is_dead())
        {
            window.draw(player.get_drawable());
        }
    }

    for (Box& box : boxes)
        window.draw(box.get_drawable());
    for (Fire& fire : fires)
        window.draw(fire.get_drawable());
    for (Bomb& bomb : bombs)
        window.draw(bomb.get_drawable());
    for (Powerup& powerup : powerups)
        window.draw(powerup.get_drawable());

    for (Menu_button& menu_botton : menu_buttons)
        window.draw(menu_button.get_drawable());
}


void Game_state::user_input_handler(sf::Mouse mouse, sf::Keyboard keyboard)
{
    for (Player& player : players)
    {
        player.update(keyboard);
    }

    if (mouse.isButtonPressed(sf::Mouse::left)
    {
        //end_game() and go to menu if quit_button.click(mouse)
        //if pause_button.click(mouse) is_playing = !is_playing
    }
}

void Game_state::new_round()
{
    for (Player& player : players)
    {
        if (!player.is_dead())
        {
            player.give_points(100);
        }
        player.new_round();
    }
    current_round += 1;
    //remove powerups, wooden_boxes, bombs, fires
    //spawn Wooden_boxes
    round_timer.restart();

}

void Game_state::new_game(int PC, int NPC1, int NPC2, int NPC3)
{
    //initialize everything
    round_timer.restart();
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
            [] (Player p) {return !p.is_dead()});

    //This works even if only one player is playing the game. In english,
    //if someone is dead and no more than one player is alive return true.
    if (players.length() > alive_players_count && alive_players_count <= 1)
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
    if (round_timer.getElapsedTime().asSeconds() > 180)
    {
        return true;
    }
    return false;
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
    if (mouse.isButtonPressed(sf::Mouse::left)
    {
        PC_button.click(mouse);
        NPC1_button.click(mouse);
        NPC2_button.click(mouse);
        NPC3_button.click(mouse);

        if (start_button.click(mouse))
        {
            nr_players = PC.get_value() + NPC1.get_value() + NPC2.get_value() + NPC3.get_value();
            if (nr_players <= 4 && nr_players != 0)
            {
                game_state.create_game(PC.get_value(),
                                    NPC1.get_value(),
                                    NPC2.get_value(),
                                    NPC3.get_value());
            }
            else
            {
                //not valid game message?
            }
        }
    }
}

void Menu_state::draw(sf::Window& window)
{
    for (Menu_button& menu_button : menu_buttons)
    {
        window.draw(menu_button.get_drawable());
    }
    //we need to somewhere give the buttons a position. Maybe that can be done here based on the size of window. We might add a scaling too.
    //And perhaps draw some fancy background
}
