#include <SFML/Graphics.hpp>
#include "Bomb.h"
#include "Player.h"

Bomb::Bomb(sf::Vector2f pos, sf::Texture texture, Player* player):
    Game_object(pos, texture), owner{player}
{}

void Bomb::spawn_fire(std::list<Wooden_box*> wooden_boxes,
	       	std::list<Solid_box*> solid_boxes,
	       	std::list<Fire*> fires)
{
	fires.push_back(new Fire fire1{});
	for (i=0, i <= radius && solidbox_at_pos(pos.x+i),i++)
	{
		fires.push_back(new Fire fire{pox.x+i,pos.y, fire_texture}); // Need a sf::Vector2f here, also needs acces to fire texture...
		if woodenbox_at_pos(pos.x+i,pos.y)
		{
			break;
		}

	}
}
