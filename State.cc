#include "State.h"
#include <SFML/Graphics.hpp>

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
            }
        }
    }

    for (Bomb& bomb : bombs)
    {
        for (Bomb& bomb2 : bombs)
        {
            if (bomb.hitbox().intersects(bomb2.hitbox()))
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

    wooden_boxes.remove_if(
            [](Wooden_box wooden_box){return wooden_box.isdead()})
}


void Game_state::draw(sf::Window& window)
{
    for (Player& player : players)
        window.draw(player.get_drawable());
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


}
