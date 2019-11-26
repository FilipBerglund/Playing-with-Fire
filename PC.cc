#include "PC.h"
#include "Player.h"
#include <iostream>


Pc::Pc(sf::Vector2f pos, sf::Texture texture, int cooldown, bool in_push,
       int in_health, int in_speed, int in_fire, int in_cd,
       sf::Keyboard::Key left_arg,
       sf::Keyboard::Key right_arg,
       sf::Keyboard::Key down_arg,
       sf::Keyboard::Key up_arg,
       sf::Keyboard::Key bomb_arg):
    Player(pos, texture, cooldown, in_push, in_health, in_speed, in_fire, in_cd),
    left{left_arg},
    right{right_arg},
    down{down_arg},
    up{up_arg},
    bomb_button{bomb_arg}
{}

void Pc::update(sf::Keyboard keyboard)
{
    std::cout << old_position.x << std::endl;
    if (keyboard.isKeyPressed(bomb_button))
    {
        want_to_drop_bomb == true;
    }
    else if (keyboard.isKeyPressed(left))
    {
        old_position = sprite.getPosition() - sf::Vector2f(-speed, 0);
        sprite.setRotation(-90);
        sprite.move(-speed, 0);
        std::cout << old_position.x << std::endl;
    }
    else if (keyboard.isKeyPressed(right))
    {
        old_position = sprite.getPosition() - sf::Vector2f(speed, 0);
        sprite.setRotation(90);
        sprite.move(speed, 0);
    }
    else if (keyboard.isKeyPressed(down))
    {
        old_position = sprite.getPosition() - sf::Vector2f(0,speed);
        sprite.setRotation(180);
        sprite.move(0, speed);
    }
    else if(keyboard.isKeyPressed(up))
    {
        old_position = sprite.getPosition() - sf::Vector2f(0, -speed);
        sprite.setRotation(0);
        sprite.move(0, -speed);
    }
}
