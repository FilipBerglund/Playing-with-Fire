#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"
#include "Bomb.h"
#include <stdlib.h>

Bomb::Bomb(sf::Vector2f pos, sf::Texture& texture, Player* player):     
    Game_object(pos, texture),
    owner{player},
    speed{3},
    fuse_timer{}
{
}

bool Bomb::is_blasted() const
{
    return fuse_timer.getElapsedTime().asSeconds() > 3;
}

void Bomb::update()
{
    old_position = sprite.getPosition();
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
          sprite.move(0,-speed);
        }
        else if (move_direction == "down")
        {
          sprite.move(0,speed);
        }
    }
    else
    {
	if ((int)old_position.x % 50 < 5 && (int)old_position.x % 50 != 0)
        {
            sprite.move(-1,0);
        }
        else if ((int)old_position.y % 50 < 5 && (int)old_position.y % 50 != 0)
        {
    	    sprite.move(0,-1);
        }
        else if ((int)old_position.y % 50 > 45 && (int)old_position.y % 50 != 0)
        {
	    sprite.move(0,1);
        }
        else if ((int)old_position.x % 50 > 45 && (int)old_position.x % 50 != 0)
        {
    	    sprite.move(1,0);
        }
    }
}

void Bomb::apply_on_hit_effect(Game_object* object)
{
    if (dynamic_cast<Player*>(object) != nullptr)
    {
        if (abs(old_position.x - object->get_old_position().x) <= 50 &&
	    abs(old_position.y - object->get_old_position().y) <= 50) 
	{
	    return;
	}
    }
    is_gliding = false;
}

void Bomb::glide(std::string direction)
{
    move_direction = direction;
    is_gliding = true;
}
