#include <SFML/Graphics.hpp>
#include "Powerup.h"
#include "Player.h"

void Speed::apply(Player player)
{
    if (player.bonus_speed < 10)
    {
        player.bonus_speed += 2;
    }
}

void Speed::update()
{}

void Bigger_blast::apply(Player player)
{
    player.fire_size += 1;
}

void Bigger_blast::update()
{}

void Extra_bomb::apply(Player player)
{
    sf::Clock clock;
    player.bomb_cds.push_back(clock);
}

void Extra_bomb::update()
{}

void Push::apply(Player player)
{
    player.push_powerup = true;
}

void Push::update()
{}
