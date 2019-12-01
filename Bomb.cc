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
        if (std::string direction == "right")
        {
	  sprite.move(speed,0);
        }
        else if (std::string direction == "left")
        {
	  sprite.move(-speed,0);
        }
        else if (std::string direction == "up")
        {
          sprite.move(0,speed);
        }
        else if (std::string direction == "down")
        {
          sprite.move(0,-speed);
        }
    }  
}

void Bomb::apply_on_hit_effect(Game_object* object)
{
  if(is_gliding = false)
    {
      sprite.setPostion(sprite.getPosition());
    }
}

void Bomb::glide()
{
  is_gliding = true;
}
