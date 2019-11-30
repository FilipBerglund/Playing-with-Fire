#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"
#include "Fire.h"
#include "Game_state.h"
#include "Bomb.h"

Bomb::Bomb (sf::Vector2f pos,
 sf::Texture & texture, Player* player):     
    Game_objects(pos, texture), owner{player}
{}

/*
 * Jag tror det är bäst om game_state spawnar fire istället.
 * Då behöver du lägga till en funktion för att returnera owner.
 * Och en boolsk funktion som säger om bomben ska "sprängas".
 */
void Bomb::set_owner(Player* owner, Fire fire)
{
  if(is_blasted == true)
    {
      return owner->fire;
    }
}

bool is_blasted() const
{
  if(ticking_bomb.getElapsedTime().asSeconds()>=timer)
    {
      return true;
    }
  else
    {
      return false;
    }
}
    

/*
 * Lägg till rörelse om is_gliding är true.
 * Läs kommentaren vid Bomb::glide.
 */

void Bomb::update() override
{
  if(is_glidding = true)
    {
        if (std::string direction == "right")
        {
	  sprite.move(2,0);
        }
        else if (std::string direction == "left")
        {
	  sprite.move(-2,0);
        }
        else if (std::string direction == "up")
        {
          sprite.move(0,2);
        }
        else if (std::string direction == "down")
        {
          sprite.move(0,-2);
        }
    }  
}


/*
 * Vi hade tänkt att Bomb skulle sluta glida då denna
 * funktion körs. Lägg till det.
 */
void Bomb::apply_on_hit_effect(Game_object* object)
{
  if(is_gliding = false)
    {
      object->undo_last_move();
    }
}

/*
 * Så som denna funktion används i player ska den bara
 * sätta is_gliding til true och sedan ändra sin
 * direction efter inparameter.
 *
 * Funktionaliteten för rörelse kan flyttas till update.
 * Där den glider bara om is_gliding är true.
 */
void Bomb::glide()
{
  is_gliding = true; 
}
