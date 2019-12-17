#include "NPC3.h"
#include "Bomb.h"
#include "Fire.h"
#include "Box.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include <iostream>
#include <stdlib.h>

Npc3::Npc3(sf::Vector2f pos, sf::Texture& texture, std::string in_name):
        Npc(pos, texture, true, 4, 2, 2, 2, in_name)
{}


//Assigns points to a position depending on what object occupies it.
int Npc3::local_score(std::string object) const
{
    if (object == "box")
    {
        return -1000;
    }
    else if (object == "fire")
    {
        return -10;
    }
    else if (object == "bomb")
    {
        return -10;
    }
    else if (object == "powerup")
    {
        return 10;
    }
    else if (object == "player")
    {
        return 2;
    }
    return 0;
}


//Help function that goes through a list of bombs.
void Npc3::score_assigner(std::list<Bomb*>& objects,
        int& up_score, int& down_score, int& right_score,
        int& left_score, int& pos_score,
        sf::Vector2f up, sf::Vector2f right) const
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
void Npc3::score_assigner(std::list<Fire*>& objects,
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
void Npc3::score_assigner(std::list<Powerup*>& objects,
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
void Npc3::score_assigner(std::list<Player*>& players,
        int& up_score, int& down_score, int& right_score,
        int& left_score, int& pos_score,
        sf::Vector2f up, sf::Vector2f right)
{
    sf::Vector2f min_dir{1000,1000};
    int scale{1};
    Player* nearest_player{nullptr};
    for (Player * player : players)
    {
        if (player != this)
        {
            if (abs(min_dir.x) + abs(min_dir.y) >
                    abs(get_position().x - player->get_position().x) +
                    abs(get_position().y - player->get_position().y))
            {
                min_dir.x = player->get_position().x - get_position().x;
                min_dir.y = player->get_position().y - get_position().y;
                nearest_player = player;
            }
        }
    }

    //The case where there is only one player.
    if (nearest_player == nullptr)
    {
        return;
    }

    if (nearest_player->hitbox().contains(sprite.getPosition() + up) ||
        nearest_player->hitbox().contains(sprite.getPosition() + up + up) ||
        nearest_player->hitbox().contains(sprite.getPosition() + up + right) ||
        nearest_player->hitbox().contains(sprite.getPosition() + up - right) ||
        nearest_player->hitbox().contains(sprite.getPosition() - up) ||
        nearest_player->hitbox().contains(sprite.getPosition() - up - up) ||
        nearest_player->hitbox().contains(sprite.getPosition() - up + right) ||
        nearest_player->hitbox().contains(sprite.getPosition() - up - right) ||
        nearest_player->hitbox().contains(sprite.getPosition() + right) ||
        nearest_player->hitbox().contains(sprite.getPosition() - right) ||
        nearest_player->hitbox().contains(sprite.getPosition()))
   {
        scale = 3;
        want_to_drop_bomb = true;
   }
   if (min_dir.x < 0)
   {
       left_score += scale*local_score("player");
   }
   else if (min_dir.x > 0)
   {
       right_score += scale*local_score("player");
   }
   if (min_dir.y < 0)
   {
       up_score += scale*local_score("player");
   }
   else if (min_dir.y > 0)
   {
       down_score += scale*local_score("player");
   }
   if (min_dir.x == 0 || min_dir.y == 0)
   {
       pos_score += scale*local_score("player");
   }
}

