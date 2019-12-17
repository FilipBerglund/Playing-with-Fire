#include "NPC1.h"
#include "Bomb.h"
#include "Fire.h"
#include "Box.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include <iostream>

Npc1::Npc1(sf::Vector2f pos, sf::Texture & texture, std::string in_name):
    Npc(pos, texture, false, 3, 1, 2, 3, in_name)
{}


//Assigns points to a position depending on what object occupies it.
int Npc1::local_score(std::string object) const
{
    if (object == "box")
    {
        return -100;
    }
    else if (object == "fire")
    {
        return -60;
    }
    else if (object == "bomb")
    {
        return -40;
    }
    else if (object == "powerup")
    {
        return 10;
    }
    else if (object == "player")
    {
        return 1;
    }
    return 0;
}

//Help function that goes through a list of bombs.
void Npc1::score_assigner(std::list<Bomb*>& objects,
        int& up_score, int& down_score, int& right_score,
        int& left_score, int& pos_score,
        sf::Vector2f up, sf::Vector2f right) const
{
    for (Game_object * object : objects)
    {
        if (object->hitbox().contains(sprite.getPosition() + up))
        {
            up_score += local_score("bomb");
        }
        if (object->hitbox().contains(sprite.getPosition() - up))
        {
            down_score += local_score("bomb");
        }
        if (object->hitbox().contains(sprite.getPosition() + right))
        {
            right_score += local_score("bomb");
        }
        if (object->hitbox().contains(sprite.getPosition() - right))
        {
            left_score += local_score("bomb");
        }
        if (object->hitbox().contains(sprite.getPosition()))
        {
            pos_score += local_score("bomb");
        }
    }
}

//Help function that goes through a list of fires.
void Npc1::score_assigner(std::list<Fire*>& objects,
        int& up_score, int& down_score, int& right_score,
        int& left_score, int& pos_score,
        sf::Vector2f up, sf::Vector2f right) const
{
    for (Game_object * object : objects)
    {
        if (object->hitbox().contains(sprite.getPosition() + up))
        {
            up_score += local_score("fire");
        }
        if (object->hitbox().contains(sprite.getPosition() - up))
        {
            down_score += local_score("fire");
        }
        if (object->hitbox().contains(sprite.getPosition() + right))
        {
            right_score += local_score("fire");
        }
        if (object->hitbox().contains(sprite.getPosition() - right))
        {
            left_score += local_score("fire");
        }
        if (object->hitbox().contains(sprite.getPosition()))
        {
            pos_score += local_score("fire")*5;
        }
    }
}

//Help function that goes through a list of powerups.
void Npc1::score_assigner(std::list<Powerup*>& objects,
        int& up_score, int& down_score, int& right_score,
        int& left_score, int& pos_score,
        sf::Vector2f up, sf::Vector2f right) const
{
    for (Game_object * object : objects)
    {
        if (object->hitbox().contains(sprite.getPosition() + up))
        {
            up_score += local_score("powerup");
        }
        if (object->hitbox().contains(sprite.getPosition() - up))
        {
            down_score += local_score("powerup");
        }
        if (object->hitbox().contains(sprite.getPosition() + right))
        {
            right_score += local_score("powerup");
        }
        if (object->hitbox().contains(sprite.getPosition() - right))
        {
            left_score += local_score("powerup");
        }
        if (object->hitbox().contains(sprite.getPosition()))
        {
            pos_score += local_score("powerup");
        }
    }
}


//Help function that goes through a list of players.
void Npc1::score_assigner(std::list<Player*>& players,
        int& up_score, int& down_score, int& right_score,
        int& left_score, int& pos_score,
        sf::Vector2f up, sf::Vector2f right)
{
    for (Player * player : players)
    {
        bool cond1 = player->hitbox().contains(sprite.getPosition() + up);
        bool cond2 = player->hitbox().contains(sprite.getPosition() - up);
        bool cond3 = player->hitbox().contains(sprite.getPosition() + right);
        bool cond4 = player->hitbox().contains(sprite.getPosition() - right);
        bool cond5 = player->hitbox().contains(sprite.getPosition());

        if ((cond1 || cond2 || cond3 || cond4 || cond5) && player != this)
        {
            want_to_drop_bomb = true;
            if (cond1)
            {
                up_score += local_score("player");
            }
            if (cond2)
            {
                down_score += local_score("player");
            }
            if (cond3)
            {
                right_score += local_score("player");
            }
            if (cond4)
            {
                left_score += local_score("player");
            }
            if (cond5)
            {
                pos_score += local_score("player");
            }
        }
    }
}
