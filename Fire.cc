#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Fire.h"

Fire::Fire(sf::Vector2f pos, sf::Texture& sprite, Player* player) 
: Game_objects(pos, sprite), owner{player}
{
  aflame_timer.getElapsedTime().asSeconds()<=3;
}

void apply_on_hit_effect(Game_object* object) override
{
  dynamic_cast<Player*>(object)->reduce_health(1);
  dynamic_cast<Wooden_box*>(object)->is_dead()==true;
}

bool Fire:: is_extinguished() const
{
  if(aflame_timer.getElapsedTime().asSeconds()>3)
    {
      return true;
    }
  
  return false;
}
