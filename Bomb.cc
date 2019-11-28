#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Fire.h"
#include "Game_state"

#include "Bomb.h"

#include <iostream>
#include <vector>

/*
 *  Använd inte namespace.
*   Skriv ut std:: då du använder det istället.
*/
using namespace std;

Bomb::Bomb (sf::Vector2f pos,/*sf::FileStream stream,*/
 sf::Texture texture, Player* player):     
    Game_objects(pos, texture), owner{player}
{
    /*
     *  Detta sköts av Game_object och behöver inte upprepas här.
    *   Du kan ta bort allt i konstruktorkroppen.
    */
    float x;
    float y;
    sprite.setPostion(x,y)
    sprite.setOrigin(hitbox().width/1, hitbox().height/1);
    //sprite.setPosition (x, y);
    //sprite.setOrigin (sprite_size.x / 2, sprite_size.y / 2);
    //stream.open("Bomb.png");
    //texture.loadFromStream(stream);
}

/*
 * Jag tror det är bäst om game_state spawnar fire istället.
 * Då behöver du lägga till en funktion för att returnera owner.
 * Och en boolsk funktion som säger om bomben ska "sprängas".
 */
void Bomb::spawn_fire(Player* owner, float timer, Fire fire)
{
    //adding owner condition

    sf::Time time= sf::Time seconds (float 3);
    float timer= ticking_bomb.getElapsedTime().asSeconds();
    for (timer <= 0)
    {
        return fire;
    }
     
}


/*
 * Lägg till rörelse om is_gliding är true.
 * Läs kommentaren vid Bomb::glide.
 */
void Bomb::update() override
{
    //update
}


/*void Bomb::collision(Game_object* object)
{
    for (object == Box || object == Bomb || object == Player)
    {
       sprite.setPosition(old_postion);
    }
    
}*/

/*
 * Vi hade tänkt att Bomb skulle sluta glida då denna
 * funktion körs. Lägg till det.
 */
void Bomb::apply_on_hit_effect(Game_object* object)
{
    object->undo_last_move();
}

//float offsetX();
//float offsetY();

/*
 * Så som denna funktion används i player ska den bara
 * sätta is_gliding til true och sedan ändra sin
 * direction efter inparameter.
 *
 * Funktionaliteten för rörelse kan flyttas till update.
 * Där den glider bara om is_gliding är true.
 */
void Bomb::glide(string direction)
{
    float offset();
    sf::Vector current = sprite.getPosition();
    //Movement = sprite.setPosition(pos.x + offsetX, pos.y + offsetY);
    if (direction == "right") {
            /*
             * Sprite har en funktion move, använd den.
             * Det behöver inte vara såhär komplicerat.
             */
            sprite.setPosition(sprite.getPosition().getRotation() + offset + angle(radius()) );
        }
        else if (direction == "left")
        {
            sprite.setPosition(sprite.getPosition().getRotation() + offset + angle(radius()) );   
        }
        else if (direction == "up")
        {
            sprite.setPosition(sprite.getPosition().getRotation() + offset + angle(radius()) );
        }
        else if (direction == "down")
        {
            sprite.setPosition(sprite.getPosition().getRotation() + offset + angle(radius()) );
        }
        else
        {
            ptr->undo_last_move();
        }
}
/*float Speed{length{idk}};
float coordinate{angle (rd)};
velocity = sf::Vector2f {Speed * cos(coordinate), Speed * sin(coordinate)};

void Bomb::glide(string direction)
{
    Bomb* ptr = 
    Bomb.move (velocity)
      if (direction == "right")
        {
            rd==360;
        }
        else if (direction == "left")
        {
            rd==180;
        }
        else if (direction == "up")
        {
            rd==90;
        }
        else if (direction == "down")
        {
            rd==270;
        }
        else
        {
            ptr->undo_last_move();
        }
        
        
        
    
    
}*/

/*
 * Tror inte att vi behöver denna funktion.
 * David har använt sig av den men jag ska säga
 * till honom att han ska ta bort det.
 */
bool Bomb::is_gliding() const
{
    /*
     * glide är inte en medläm, det ska den inte vara heller.
     * Denna funktion ska bara returnera om den glider eller inte.
     */
    if (is_gliding == false)
    {
        return glide;
    }
    else
    {
        sprite.setpostion(old_position);
    }
    
}

/*
 * Tror inte vi behöver denna funktion.
 * Det är bara bomben som ändrar i is_gliding
 * så vi behöve ha en funktion för det.
 */
void Bomb::set_is_gliding(bool sam)
{
    is_gliding = sam;
}
