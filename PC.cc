#include "PC.h"


PC::PC(sf::Vector2f pos, sf::Texture texture, int cooldown, int in_push,
       int in_health, int in_speed, int in_fire, int in_cd,
       sf::Key left_arg, sf::Key right_arg, sf::Key down_arg, sf::Key up_arg, sf::key bomb_arg):
    Player(pos, texture, cooldown, in_push, in_health, in_speed, in_fire, in_cd),
    left{left_arg},
    right{right_arg},
    down{down_arg},
    up{up_arg},
    bomb_button{bomb_arg}
{}

void update(sf::Keyboard keyboard)
{
    if (keyboard.isKeyPressed(bomb_button) == true)
    {
	want_to_drop_bomb == true;
    }
    else if (keyboard.isKeyPressed(left) == true)
    {
	sprite.setRotation(-90);
	sprite.move(-speed, 0):
    }
    else if (keyboard.isKeyPressed(right) == true)
    {
	sprite.setRotation(90);
	sprite.move(speed, 0);
    }
    else if keyboard.isKeyPressed(down) == true()
    {
	sprite.rotation(180);
	sprite.move(0, speed);
    }
    else if(keyboard.isKeyPressed(up) == true)
    {
	sprite.setRotation(0);
	sprite.move(0, -speed);
    }
}
