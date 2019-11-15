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

void Bigger_blast::apply(Player player)
{
    player.blast_radius += 2;
}

void Extra_bomb::apply(Player player)
{
    sf::Clock clock;
    player.bomb_cds.append(clock);
}

void Push::apply(Player player)
{
    player.push_powerup = true;
}
