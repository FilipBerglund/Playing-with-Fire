#include <Player.h>
#include <SFML/Graphics.hpp>
#include <string>

NPC::NPC(sf::Vector2f pos, sf::Texture & texture, int cooldown, bool in_push,
         int in_health, int in_speed, int in_fire, int in_cd, std::string in_name):
    Player(pos, texture, cooldown, in_push, in_health, in_speed, in_fire, in_cd, in_name)
{}

int local_score(std::string object) const
{
    if (object == "powerup")
    {
	return 3;
    }
    else if (object == "fire")
    {
	return -60;
    }
    else if (object == "bomb without push")
    {
	return -40;
    }
    else if (object == "box")
    {
	return -20;
    }
    else if (object == "player")
    {
	return 2:
    }
    else if (object == "empty space")
    {
	return 1;
    }
    return 0;  //0 will not be returned in practise, this line simply keeps the compiler content. 
}

void NPC::update(std::)
{
    int left{0};
    int right{0};
    int up{0};
    int low{0};
    int cur{0};
    
    if ()
    {
	
    }
}
