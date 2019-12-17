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
    Player* player = dynamic_cast<Player*>(object);
    if (player != nullptr && !(player->is_immune()))
    {
        player->reduce_health(1);
        player->make_immune();
        if (player!=owner)
        {
            owner->increase_score(25);
        }
        return;
    }
    Wooden_box* wooden_box = dynamic_cast<Wooden_box*>(object);
    if (wooden_box != nullptr)
    {
        wooden_box->reduce_health(1);
    }
}

bool Fire::is_extinguished() const
{
    return aflame_timer.getElapsedTime().asSeconds() > 3;
}
