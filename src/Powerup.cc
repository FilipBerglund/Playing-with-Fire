#include <SFML/Graphics.hpp>
#include "Powerup.h"
#include "Player.h"

void Speed::apply_on_hit_effect(Game_object* player)
{
    Player* p = dynamic_cast<Player*>(player);
    if (p->get_speed() < 4)
    {
        p->increase_speed(1);
    }
}

void Bigger_blast::apply_on_hit_effect(Game_object* player)
{
    dynamic_cast<Player*>(player)->increase_fire_size(1);
}

void Extra_bomb::apply_on_hit_effect(Game_object* player)
{
    dynamic_cast<Player*>(player)->give_bomb();
}

void Push::apply_on_hit_effect(Game_object* player)
{
    dynamic_cast<Player*>(player)->set_push_powerup(true);
}
