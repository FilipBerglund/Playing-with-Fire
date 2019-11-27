#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Fire.h"
#include "Game_state"

#include "Bomb.h"

#include <iostream>
#include <vector>
using namespace std;

Bomb::Bomb (sf::Vector2f pos,/*sf::FileStream stream,*/
 sf::Texture texture, Player* player):     
    Game_objects(pos, texture), owner{player}
{
    float x;
    float y;
    sprite.setPostion(x,y)
    sprite.setOrigin(hitbox().width/1, hitbox().height/1);
    //sprite.setPosition (x, y);
    //sprite.setOrigin (sprite_size.x / 2, sprite_size.y / 2);
    //stream.open("Bomb.png");
    //texture.loadFromStream(stream);
}

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

void Bomb::apply_on_hit_effect(Game_object* object)
{
    object->undo_last_move();
}

//float offsetX();
//float offsetY();

void Bomb::glide(string direction)
{
    sf::Vector current = sprite.getPosition();
    //Movement = sprite.setPosition(pos.x + offsetX, pos.y + offsetY);
    if (direction == "right")
        {
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

bool Bomb::is_gliding() const
{
    if (is_gliding == false)
    {
        return glide;
    }
    else
    {
        sprite.setpostion(old_position);
    }
    
}

void Bomb::set_is_gliding(bool sam)
{
    is_gliding = sam;
}
