#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"
//#include "Fire.h"
#include "Bomb.h"

Bomb::Bomb (sf::Vector2f pos,
 sf::Texture & texture, Player* player):     
    Game_objects(pos, texture), owner{player}
{}

/*
void Bomb::set_owner(Player* owner, Fire fire)
{
  if(is_blasted == true)
    {
       Player* owner = &fire;
       return owner;
    }
}
*/
bool is_blasted() const
{
  if(fuse_timer.getElapsedTime().asSeconds()>3)
    {
      return true;
    }
  else
    {
      return false;
    }
}

void Bomb::update() override
{
  if(is_glidding = true)
    {
        if (move_direction == "right")
        {
	  sprite.move(speed,0);
        }
        else if (move_direction == "left")
        {
	  sprite.move(-speed,0);
        }
        else if (move_direction == "up")
        {
          sprite.move(0,speed);
        }
        else if (move_direction == "down")
        {
          sprite.move(0,-speed);
        }
    }  
}

void Bomb::apply_on_hit_effect(Game_object* object)
{
  is_gliding = false;
}

void Bomb::glide(std::string direction )
{
  direction == move_direction;
  is_gliding = true;
}
