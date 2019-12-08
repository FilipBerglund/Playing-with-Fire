#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"
#include "Bomb.h"

Bomb::Bomb(sf::Vector2f pos, sf::Texture& texture, Player* player):     
    Game_objects(pos, texture),
    owner{player},
    speed{3}
    fuse_timer{}
{}

bool is_blasted() const
{
    return fuse_timer.getElapsedTime().asSeconds() > 3;
}

void Bomb::update()
{
  if(is_gliding)
    {
        if (move_direction == "right")
        {
	  sprite.move(speed,0);
        }
        else if (move_direction == "left")
        {
	  sprite.move(-speed,0);
        }
        else if (move_direction == "up")
        {
          sprite.move(0,speed);
        }
        else if (move_direction == "down")
        {
          sprite.move(0,-speed);
        }
    }
}

void Bomb::apply_on_hit_effect(Game_object*)
{
    is_gliding = false;
}

void Bomb::glide(std::string direction)
{
    move_direction = direction;
    is_gliding = true;
}
