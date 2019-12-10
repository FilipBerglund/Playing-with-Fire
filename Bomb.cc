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
	fires.push_back(new Fire fire1{});
	for (int i=0; i <= radius && solidbox_at_pos(pos.x+i, pos.y);i++)
	{
        sf::Vector2f newPos{pos.x + i, pos.y};
		fires.push_back(new Fire fire{newPos, fire_texture});
		if (woodenbox_at_pos(pos.x+i,pos.y))
		{
			break;
		}
    }
	for (int i=0; i <= radius && solidbox_at_pos(pos.x-i,pos.y);i++)
	{
		fires.push_back(new Fire fire{pox.x-i,pos.y, fire_texture}); 
		if (woodenbox_at_pos(pos.x-i,pos.y))
		{
			break;
		}
	}
	for (int i=0; i <= radius && solidbox_at_pos(pos.x,pos.y+i);i++)
	{
		fires.push_back(new Fire fire{pox.x,pos.y+i, fire_texture}); 
		if (woodenbox_at_pos(pos.x,pos.y+i))
		{
			break;
		}
    }
	for (int i=0; i <= radius && solidbox_at_pos(pos.x,pos.y-i);i++)
	{
		fires.push_back(new Fire fire{pox.x,pos.y-i, fire_texture}); 
		if (woodenbox_at_pos(pos.x,pos.y-i))
		{
			break;
		}
    }
}
