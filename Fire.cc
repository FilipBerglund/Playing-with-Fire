#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Fire.h"

Fire::Fire(sf::Vector2f pos, sf::Texture& texture, Player* player):
    Game_objects(pos, texture), 
    owner{player},
    aflame_timer{}
{}

void apply_on_hit_effect(Game_object* object)
{
    dynamic_cast<Player*>(object)->reduce_health(1);
}

bool Fire::is_extinguished() const
{
    return aflame_timer.getElapsedTime().asSeconds()>3;
}
