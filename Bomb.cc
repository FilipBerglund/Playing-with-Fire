#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Fire.h"
#include "Game_state"

#include "Bomb.h"

#include <iostream>
using namespace std;

Bomb::Bomb (sf::Vector2f pos, sf::Sprite sprite, Player* owner):     
    Game_objects(pos, sprite), owner{player}
{}

void Bomb::spawn_fire(Player* owner, int timer, Fire fire)
{
    //adding owner condition
    if (timer==0)
    {
        return fire;
    }
     
}


void Bomb::update()
{

}


void Bomb::collision(Game_object* object)
{
    for (object == Box || object == Bomb || object == Player)
    {
       sprite.setPosition(old_postion);
    }
    
}


void Bomb::glide(string direction)
{
    Bomb* popo;
      if (direction == "right")
        {
            /*bomb moves right till collision*/
            
        }
        else if (direction == "left")
        {
            /* bomb moves left till collision */
        }
        else if (direction == "up")
        {
            /* bomb moves up till collision */
        }
        else if (direction == "down")
        {
            /* bomb moves down till collision */
        }
        else
        {
            popo->sprite.setposition(popo->old_position)
        }
        
        
        
    
    
}

bool Bomb::is_gliding() const
{
    if (is_gliding == false)
    {
        return glide;
    }
    else
    {
        sprite.setpostion(old.position);
    }
    
}

void Bomb::set_is_gliding(bool sam)
{
    is_gliding = sam;
}