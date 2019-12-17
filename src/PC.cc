#include "PC.h"
#include "Player.h"
#include <iostream>


Pc::Pc(sf::Vector2f pos, sf::Texture & texture, bool in_push,
       int in_health, int in_speed, int in_fire, int in_cd, std::string in_name,
       sf::Keyboard::Key left_arg,
       sf::Keyboard::Key right_arg,
       sf::Keyboard::Key down_arg,
       sf::Keyboard::Key up_arg,
       sf::Keyboard::Key bomb_arg):
    Player(pos, texture, in_push, in_health, in_speed, in_fire, in_cd, in_name),
    left{left_arg},
    right{right_arg},
    down{down_arg},
    up{up_arg},
    bomb_button{bomb_arg}
{}

//update looks to see if a button which belongs to the player has been pressed.
//If this is the case the player either moves or attempts to drop a bomb.
void Pc::update(sf::Keyboard keyboard)  
{
    old_position = sprite.getPosition();
    if (keyboard.isKeyPressed(bomb_button) && !previous_bomb_button)
    {
        want_to_drop_bomb = true;
        previous_bomb_button = true;
	//previous_bomb_button is a help variable which simply makes sure
	//that when the bomb_button is pressed the player does not drop 2 bombs
	//almost at the same time. In order to drop a second bomb the player has to
	//repress the bomb_button and not just hold it in. 
    }
    else if (!keyboard.isKeyPressed(bomb_button))
    {
	previous_bomb_button = false;
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
}
