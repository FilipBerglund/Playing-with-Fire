#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Game_state"
#include "Fire.h"

Fire::Fire(sf::Vector2f pos, sf::Texture& sprite, Player* player) 
: Game_objects(pos, sprite), owner{player}
{
  //init timer
  std::initializer
}

bool is_dead() const
{
  return;
}

void Fire::give_points(Player* owner)
{
      return owner->increase_point(1);
}

void update() override
{
  //Uppdaterar eldens tillstånd
}
