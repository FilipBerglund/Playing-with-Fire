//TODO: Se över vilka includes som behöver finnas.
//Game_state finns inte. iostream och vector
//används inte här så de ska bort.
#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"
//#include "Fire.h"
#include "Bomb.h"

<<<<<<< HEAD
Bomb::Bomb (sf::Vector2f pos,
 sf::Texture & texture, Player* player):     
=======
#include <iostream>
#include <vector>

/*
 * TODO: Använd inte namespace.
 * Skriv ut std:: då du använder det istället.
*/
using namespace std;

Bomb::Bomb (sf::Vector2f pos,/*sf::FileStream stream,*/
 sf::Texture texture, Player* player):     
>>>>>>> 93411fa2be2e3b8d5e9a5a3861169f1b421033ab
    Game_objects(pos, texture), owner{player}
{}

/*
<<<<<<< HEAD
void Bomb::set_owner(Player* owner, Fire fire)
=======
 * TODO: Anders implementerar denna funktion.
 */
void Bomb::spawn_fire(Player* owner, float timer, Fire fire)
>>>>>>> 93411fa2be2e3b8d5e9a5a3861169f1b421033ab
{
  if(is_blasted == true)
    {
       Player* owner = &fire;
       return owner;
    }
}
<<<<<<< HEAD
*/
bool is_blasted() const
=======


/*
 * TODO: Lägg till rörelse om is_gliding är true.
 * Läs kommentaren vid Bomb::glide.
 */
void Bomb::update() override
{
    //update
}


/*
 * TODO: collision funktionen finns inte längre.
 */
/*void Bomb::collision(Game_object* object)
>>>>>>> 93411fa2be2e3b8d5e9a5a3861169f1b421033ab
{
  if(fuse_timer.getElapsedTime().asSeconds()>3)
    {
      return true;
    }
  else
    {
      return false;
    }
<<<<<<< HEAD
}

void Bomb::update() override
=======
    
}*/

/*
 * TODO: Vi hade tänkt att Bomb skulle sluta glida då denna
 * funktion körs. Lägg till det. Den ska inte stoppa
 * objectet som colliderar med den, dvs det ska gå att
 * gå igenom bomber.
 */
void Bomb::apply_on_hit_effect(Game_object* object)
{
    object->undo_last_move();
}

//float offsetX();
//float offsetY();

/*
 * TODO: Så som denna funktion används i player ska den bara
 * sätta is_gliding till true och sedan ändra sin
 * direction efter inparameter. Så se till att det
 * finns medlämmar i Bomb.h för direction och is_gliding.
 * (std::string respektive bool)
 *
 * Funktionaliteten för rörelse kan flyttas till update.
 * Där den glider bara om is_gliding är true.
 */
void Bomb::glide(string direction)
>>>>>>> 93411fa2be2e3b8d5e9a5a3861169f1b421033ab
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

<<<<<<< HEAD
void Bomb::apply_on_hit_effect(Game_object* object)
{
  if(is_gliding = false)
=======
/*
 * TODO: Tror inte att vi behöver denna funktion.
 * David har använt sig av den men jag ska säga
 * till honom att han ska ta bort det.
 */
bool Bomb::is_gliding() const
{
    if (is_gliding == false)
>>>>>>> 93411fa2be2e3b8d5e9a5a3861169f1b421033ab
    {
      sprite.setPostion(sprite.getPosition());
    }
}

<<<<<<< HEAD
void Bomb::glide()
=======
/*
 * TODO: Tror inte vi behöver denna funktion.
 * Det är bara bomben som ändrar i is_gliding
 * så vi behöver inte ha en funktion för det.
 */
void Bomb::set_is_gliding(bool sam)
>>>>>>> 93411fa2be2e3b8d5e9a5a3861169f1b421033ab
{
  is_gliding = true;
}
