#include "PC.h"
#include "Player.h"
#include <iostream>


Pc::Pc(sf::Vector2f pos, sf::Texture & texture, int cooldown, bool in_push,
       int in_health, int in_speed, int in_fire, int in_cd, std::string in_name,
       sf::Keyboard::Key left_arg,
       sf::Keyboard::Key right_arg,
       sf::Keyboard::Key down_arg,
       sf::Keyboard::Key up_arg,
       sf::Keyboard::Key bomb_arg):
    Player(pos, texture, cooldown, in_push, in_health, in_speed, in_fire, in_cd, in_name),
    left{left_arg},
    right{right_arg},
    down{down_arg},
    up{up_arg},
    bomb_button{bomb_arg}
{}

void Pc::update(sf::Keyboard keyboard)
{
    old_position = sprite.getPosition();
    if (keyboard.isKeyPressed(bomb_button))
    {
        want_to_drop_bomb = true;
    }
    if (keyboard.isKeyPressed(left))
    {
        sprite.setRotation(-90);
        sprite.move(-speed, 0);
    }
    else if (keyboard.isKeyPressed(right))
    {
        sprite.setRotation(90);
        sprite.move(speed, 0);
    }
    else if (keyboard.isKeyPressed(down))
    {
        sprite.setRotation(180);
        sprite.move(0, speed);
    }
    else if(keyboard.isKeyPressed(up))
    {
        sprite.setRotation(0);
        sprite.move(0, -speed);
    }
    else if ((int)old_position.x % 50 < 15 && (int)old_position.x % 50 != 0) 
    {
    	sprite.move(-1,0);
    }
    else if ((int)old_position.y % 50 < 15 && (int)old_position.y % 50 != 0)
    {
    	sprite.move(0,-1);
    }
    else if ((int)old_position.y % 50 > 35 && (int)old_position.y % 50 != 0)
    {
    	sprite.move(0,1);
    }
    else if ((int)old_position.x % 50 > 35 && (int)old_position.x % 50 != 0)
    {
    	sprite.move(1,0);
    }
}
