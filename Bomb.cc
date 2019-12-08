#include <SFML/Graphics.hpp>
#include "Bomb.h"
#include "Player.h"

Bomb::Bomb(sf::Vector2f pos, sf::Texture& texture, Player* player):
    Game_object(pos, texture), owner{player}
{}
