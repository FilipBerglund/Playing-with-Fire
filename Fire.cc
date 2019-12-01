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

<<<<<<< HEAD
bool is_dead() const
=======
//TODO: Denna behövs inte.
bool Fire::is_boosted()
{
    if (/*player boosted is applied*/)
    {
        return fire_boost;
    }
    else
    {
        /* code */
    }
    

}
//TODO: Denna behövs inte.
void Fire::fire_boost(int fire_size)
>>>>>>> 93411fa2be2e3b8d5e9a5a3861169f1b421033ab
{
  return;
}
<<<<<<< HEAD

void Fire::give_points(Player* owner)
=======
//TODO: Denna behövs inte.
void Fire::give_points(Player owner)
>>>>>>> 93411fa2be2e3b8d5e9a5a3861169f1b421033ab
{
      return owner->increase_point(1);
}

void update() override
{
<<<<<<< HEAD
  //Uppdaterar eldens tillstånd
=======

>>>>>>> 93411fa2be2e3b8d5e9a5a3861169f1b421033ab
}
