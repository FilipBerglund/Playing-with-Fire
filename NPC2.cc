#include "NPC2.h"
#include "Bomb.h"
#include "Fire.h"
#include "Box.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include <iostream>

Npc2::Npc2(sf::Vector2f pos, sf::Texture& texture, std::string in_name):
    Npc(pos, texture, false, 3, 2, 2, 3, in_name)
{}


//Assigns points to a position depending on what object occupies it.
int Npc2::local_score(std::string object) const
{
    if (object == "box")
    {
	return -1000;
    }
    else if (object == "fire")
    {
	return -30;
    }
    else if (object == "bomb")
    {
	return -10;
    }
    else if (object == "powerup")
    {
	return 1;
    }
    else if (object == "player")
    {
	if (health > 1)
	{
	    return 1;
	}
	return -4;
    }
    return 0;
}

//Help function that goes through a list of bombs.
void Npc2::score_assigner(std::list<Bomb*>& objects, int& up_score, int& down_score, int& right_score,
			 int& left_score, int& pos_score, sf::Vector2f up, sf::Vector2f right) const
{
    for (Game_object * object : objects)
    {
	if (object->hitbox().contains(sprite.getPosition() + up) ||
	    object->hitbox().contains(sprite.getPosition() + up + up) ||
	    object->hitbox().contains(sprite.getPosition() + up + right) ||
	    object->hitbox().contains(sprite.getPosition() + up - right))
	{
	    up_score += local_score("bomb");
	}
	if (object->hitbox().contains(sprite.getPosition() - up) ||
	    object->hitbox().contains(sprite.getPosition() - up - up) ||
	    object->hitbox().contains(sprite.getPosition() - up + right) ||
	    object->hitbox().contains(sprite.getPosition() - up - right))
	{
	    down_score += local_score("bomb");
	}
	if (object->hitbox().contains(sprite.getPosition() + right) ||
	    object->hitbox().contains(sprite.getPosition() + right + right) ||
	    object->hitbox().contains(sprite.getPosition() + right + up) ||
	    object->hitbox().contains(sprite.getPosition() + right - up))
	{
	    right_score += local_score("bomb");
	}
	if (object->hitbox().contains(sprite.getPosition() - right) ||
	    object->hitbox().contains(sprite.getPosition() - right - right) ||
	    object->hitbox().contains(sprite.getPosition() - right + up) ||
	    object->hitbox().contains(sprite.getPosition() - right - up))
	{
	    left_score += local_score("bomb");
	}
	if (object->hitbox().contains(sprite.getPosition()))
	{
	    pos_score += local_score("bomb")*2;
	}
    }
}

//Help function that goes through a list of fires.
void Npc2::score_assigner(std::list<Fire*>& objects, int& up_score, int& down_score, int& right_score,
			 int& left_score, int& pos_score, sf::Vector2f up, sf::Vector2f right) const
{
    for (Game_object * object : objects)
    {
	if (object->hitbox().contains(sprite.getPosition() + up))
	{
	    up_score += local_score("fire");
	}
	if (object->hitbox().contains(sprite.getPosition() + up))
	{
	    up_score += local_score("fire")/2;
	}
	if (object->hitbox().contains(sprite.getPosition() - up))
	{
	    down_score += local_score("fire");
	}
	if (object->hitbox().contains(sprite.getPosition() - up - up))
	{
	    down_score += local_score("fire")/2;
	}
	if (object->hitbox().contains(sprite.getPosition() + right))
	{
	    right_score += local_score("fire");
	}
	if (object->hitbox().contains(sprite.getPosition() + right + right))
	{
	    right_score += local_score("fire")/2;
	}
	if (object->hitbox().contains(sprite.getPosition() - right))
	{
	    left_score += local_score("fire");
	}
	if (object->hitbox().contains(sprite.getPosition() - right - right))
	{
	    left_score += local_score("fire")/2;
	}
	if (object->hitbox().contains(sprite.getPosition()))
	{
	    pos_score += local_score("fire")*5;
	}
    }
}

//Help function that goes through a list of powerups.
void Npc2::score_assigner(std::list<Powerup*>& objects, int& up_score, int& down_score, int& right_score,
			 int& left_score, int& pos_score, sf::Vector2f up, sf::Vector2f right) const
{
    for (Game_object * object : objects)
    {
	if (object->hitbox().contains(sprite.getPosition() + up))
	{
	    up_score += local_score("powerup");
	}
	if (object->hitbox().contains(sprite.getPosition() + up + up))
	{
	    up_score += local_score("powerup")/2;
	}
	if (object->hitbox().contains(sprite.getPosition() - up))
	{
	    down_score += local_score("powerup");
	}
      	if (object->hitbox().contains(sprite.getPosition() - up - up))
	{
	    down_score += local_score("powerup")/2;
	}
	if (object->hitbox().contains(sprite.getPosition() + right))
	{
	    right_score += local_score("powerup");
	}
	if (object->hitbox().contains(sprite.getPosition() + right + right))
	{
	    right_score += local_score("powerup")/2;
	}	
	if (object->hitbox().contains(sprite.getPosition() - right))
	{
	    left_score += local_score("powerup");
	}
	if (object->hitbox().contains(sprite.getPosition() - right - right))
	{
	    left_score += local_score("powerup")/2;
	}
	if (object->hitbox().contains(sprite.getPosition()))
	{
	    pos_score += local_score("powerup");
	}
    }
}

//Help function that goes through a list of players.
void Npc2::score_assigner(std::list<Player*>& objects, int& up_score, int& down_score, int& right_score,
			 int& left_score, int& pos_score, sf::Vector2f up, sf::Vector2f right) 
{
    for (Game_object * object : objects)
    {
	if (object != this)
        {
	    if (object->hitbox().contains(sprite.getPosition() + up) ||
	        object->hitbox().contains(sprite.getPosition() + up + up) ||
	        object->hitbox().contains(sprite.getPosition() + up + right) ||
	        object->hitbox().contains(sprite.getPosition() + up - right))
	    {
	        up_score += local_score("Player");
		want_to_drop_bomb = true;
	    }
	    if (object->hitbox().contains(sprite.getPosition() - up) ||
	        object->hitbox().contains(sprite.getPosition() - up - up) ||
	        object->hitbox().contains(sprite.getPosition() - up + right) ||
	        object->hitbox().contains(sprite.getPosition() - up - right))
	    {
	        down_score += local_score("Player");
		want_to_drop_bomb = true;
	    }
	    if (object->hitbox().contains(sprite.getPosition() + right) ||
	        object->hitbox().contains(sprite.getPosition() + right + right) ||
	        object->hitbox().contains(sprite.getPosition() + right + up) ||
	        object->hitbox().contains(sprite.getPosition() + right - up))
	    {
	        right_score += local_score("Player");
		want_to_drop_bomb = true;
	    }
	    if (object->hitbox().contains(sprite.getPosition() - right) ||
	        object->hitbox().contains(sprite.getPosition() - right - right) ||
	        object->hitbox().contains(sprite.getPosition() - right + up) ||
	        object->hitbox().contains(sprite.getPosition() - right - up))
	    {
	        left_score += local_score("Player");
		want_to_drop_bomb = true;
	    }
  	    if (object->hitbox().contains(sprite.getPosition()))
	    {
	        pos_score += local_score("Player");
		want_to_drop_bomb = true;
	    }
	}
    }
}
