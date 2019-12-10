#include <SFML/Graphics.hpp>
#include "Bomb.h"
#include "Player.h"

Bomb::Bomb(sf::Vector2f pos, sf::Texture texture, Player* player):
    Game_object(pos, texture), owner{player}
{}

void Bomb::spawn_fire(std::list<Wooden_box*> wooden_boxes,
	       	std::list<Solid_box*> solid_boxes,
	       	std::list<Fire*> fires,
            sf::Texture fire_texture)
{
    sf::Vector2f pos{get_position()};
	fires.push_back(new Fire fire1{pos, fire_texture, owner});
	for (int i=0; i <= radius && obj_at_pos(solid_boxes, pos.x+50*i, pos.y);i++)
	{
        sf::Vector2f newPos{pos.x + 50*i, pos.y};
		fires.push_back(new Fire fire{newPos, fire_texture, owner});
		if (obj_at_pos(wooden_boxes, pos.x+50*i, pos.y))
		{
			break;
		}
    }
	for (int i=0; i <= radius && obj_at_pos(solid_boxes, pos.x-50*i,pos.y);i++)
	{
        sf::Vector2f newPos{pos.x - 50*i, pos.y};
		fires.push_back(new Fire fire{newPos, fire_texture, owner}); 
		if (obj_at_pos(wooden_boxes, pos.x-50*i, pos.y))
		{
			break;
		}
	}
	for (int i=0; i <= radius && obj_at_pos(solid_boxes, pos.x,pos.y+50*i);i++)
	{
        sf::Vector2f newPos{pos.x, pos.y + 50*i};
		fires.push_back(new Fire fire{newPos, fire_texture, owner}); 
		if (obj_at_pos(wooden_boxes, pos.x, pos.y+50*i))
		{
			break;
		}
    }
	for (int i=0; i <= radius && obj_at_pos(solid_boxes, pos.x,pos.y-50*i);i++)
	{
        sf::Vector2f newPos{pos.x, pos.y - 50*i};
		fires.push_back(new Fire fire{newPos, fire_texture, owner}); 
		if (obj_at_pos(wooden_boxes, pos.x, pos.y-50*i))
		{
			break;
		}
    }
}

bool Bomb::obj_at_pos(std::list<Game_object*> & lst, float & x, float & y) const
{
    for (Game_object* obj :  lst)
    {
        if (obj->get_position().x == x && obj->get_position().y == y)
        {
            return true;
        }
    }
    return false;
}
