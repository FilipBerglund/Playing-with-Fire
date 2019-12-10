#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"
#include "Bomb.h"
#include "Fire.h"
#include <stdlib.h>

Bomb::Bomb(sf::Vector2f pos, sf::Texture& texture, Player* player):     
    Game_object(pos, texture),
    owner{player},
    speed{3},
    fuse_timer{},
    is_gliding{false}
{}

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

void Bomb::spawn_fire(std::list<Wooden_box*> wooden_boxes,
	       	std::list<Solid_box*> solid_boxes,
	       	std::list<Fire*> fires,
            sf::Texture fire_texture)
{
    int roundedx = (((int)get_position().x + 25) / 50 ) * 50;
    int roundedy = (((int)get_position().y + 25) / 50 ) * 50;
    sprite.setPosition(roundedx, roundedy);

    sf::Vector2f pos{get_position()};
	fires.push_back(new Fire {pos, fire_texture, owner});
	for (int i=0; i <= radius && solidbox_at_pos(solid_boxes, pos.x+50*i, pos.y);i++)
	{
        sf::Vector2f newPos{pos.x + 50*i, pos.y};
		fires.push_back(new Fire {newPos, fire_texture, owner});
		if (woodenbox_at_pos(wooden_boxes, pos.x+50*i, pos.y))
		{
			break;
		}
    }
	for (int i=0; i <= radius && solidbox_at_pos(solid_boxes, pos.x-50*i,pos.y);i++)
	{
        sf::Vector2f newPos{pos.x - 50*i, pos.y};
		fires.push_back(new Fire {newPos, fire_texture, owner}); 
		if (woodenbox_at_pos(wooden_boxes, pos.x-50*i, pos.y))
		{
			break;
		}
	}
	for (int i=0; i <= radius && solidbox_at_pos(solid_boxes, pos.x,pos.y+50*i);i++)
	{
        sf::Vector2f newPos{pos.x, pos.y + 50*i};
		fires.push_back(new Fire {newPos, fire_texture, owner}); 
		if (woodenbox_at_pos(wooden_boxes, pos.x, pos.y+50*i))
		{
			break;
		}
    }
	for (int i=0; i <= radius && solidbox_at_pos(solid_boxes, pos.x,pos.y-50*i);i++)
	{
        sf::Vector2f newPos{pos.x, pos.y - 50*i};
		fires.push_back(new Fire {newPos, fire_texture, owner}); 
		if (woodenbox_at_pos(wooden_boxes, pos.x, pos.y-50*i))
		{
			break;
		}
    }
}

bool Bomb::solidbox_at_pos(std::list<Solid_box*> & lst, float x, float y) const
{
    for (Solid_box* obj :  lst)
    {
        if (obj->get_position().x == x && obj->get_position().y == y)
        {
            return true;
        }
    }
    return false;
}

bool Bomb::woodenbox_at_pos(std::list<Wooden_box*> & lst, float x, float y) const
{
    for (Wooden_box* obj :  lst)
    {
        if (obj->get_position().x == x && obj->get_position().y == y)
        {
            return true;
        }
    }
    return false;
}
