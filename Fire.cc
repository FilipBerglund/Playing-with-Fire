#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Fire.h"

Fire::Fire(sf::Vector2f pos, sf::Texture& texture, Player* player):
    Game_object(pos, texture), 
    owner{player},
    aflame_timer{}
{}

Fire::~Fire()
{
    owner = nullptr;
    delete owner;
}

void Fire::apply_on_hit_effect(Game_object* object)
{
    Player* ptr1 = dynamic_cast<Player*>(object);
    if (ptr1 != nullptr && !(ptr1->is_immune()))
    {
	ptr1->reduce_health(1);
        ptr1->make_immune();
	return;
    }
    Wooden_box* ptr2 = dynamic_cast<Wooden_box*>(object);
    if (ptr2 != nullptr)
    {
	ptr2->reduce_health(1);
    }
}

bool Fire::is_extinguished() const
{
    return aflame_timer.getElapsedTime().asSeconds() > 3;
}
