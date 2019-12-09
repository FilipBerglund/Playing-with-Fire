#include "NPC.h"
#include "Bomb.h"
#include "Fire.h"
#include "Box.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <algorithm> 
#include <functional>
#include <stdlib.h>     
#include <time.h>
#include <list>

#include <iostream>

Npc::Npc(sf::Vector2f pos, sf::Texture & texture, bool in_push,
         int in_health, int in_speed, int in_fire, int in_cd, std::string in_name):
    Player(pos, texture, in_push, in_health, in_speed, in_fire, in_cd, in_name)
{
    direction = sf::Vector2f(0,0);
}

int Npc::local_score(std::string object) const
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

void Npc::score_assigner(std::list<Bomb*>& objects, int& up_score, int& down_score, int& right_score,
			 int& left_score, int& pos_score, sf::Vector2f up, sf::Vector2f right) const
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

void Npc::score_assigner(std::list<Fire*>& objects, int& up_score, int& down_score, int& right_score,
			 int& left_score, int& pos_score, sf::Vector2f up, sf::Vector2f right) const
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
	    pos_score += local_score("fire");
	}
    }
}

void Npc::score_assigner(std::list<Powerup*>& objects, int& up_score, int& down_score, int& right_score,
			 int& left_score, int& pos_score, sf::Vector2f up, sf::Vector2f right) const
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

void Npc::score_assigner(std::list<Wooden_box*>& objects, int& up_score, int& down_score, int& right_score,
			 int& left_score, int& pos_score, sf::Vector2f up, sf::Vector2f right) const
{
    for (Game_object * object : objects)
    {
	if (object->hitbox().contains(sprite.getPosition() + up))
	{
	    up_score += local_score("box");
	}
	if (object->hitbox().contains(sprite.getPosition() - up))
	{
	    down_score += local_score("box");
	}
	if (object->hitbox().contains(sprite.getPosition() + right))
	{
	    right_score += local_score("box");
	}
	if (object->hitbox().contains(sprite.getPosition() - right))
	{
	    left_score += local_score("box");
	}
	if (object->hitbox().contains(sprite.getPosition()))
	{
	    pos_score += local_score("box");
	}
    }
}

void Npc::score_assigner(std::list<Solid_box*>& objects, int& up_score, int& down_score, int& right_score,
			 int& left_score, int& pos_score, sf::Vector2f up, sf::Vector2f right) const
{
    for (Game_object * object : objects)
    {
	if (object->hitbox().contains(sprite.getPosition() + up))
	{
	    up_score += local_score("box");
	}
	if (object->hitbox().contains(sprite.getPosition() - up))
	{
	    down_score += local_score("box");
	}
	if (object->hitbox().contains(sprite.getPosition() + right))
	{
	    right_score += local_score("box");
	}
	if (object->hitbox().contains(sprite.getPosition() - right))
	{
	    left_score += local_score("box");
	}
	if (object->hitbox().contains(sprite.getPosition()))
	{
	    pos_score += local_score("box");
	}
    }
}

void Npc::score_assigner(std::list<Player*>& players, int& up_score, int& down_score, int& right_score,
			 int& left_score, int& pos_score, sf::Vector2f up, sf::Vector2f right) 
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

void Npc::update(std::list<Player*>& players, std::list<Bomb*>& bombs, std::list<Fire*>& fires,
		 std::list<Powerup*>& powerups, std::list<Wooden_box*>& wooden_boxes, std::list<Solid_box*>& solid_boxes)
{
    old_position = sprite.getPosition();
    


    bool at_mid{((int)old_position.x) % 50 == 0 && ((int)old_position.y) % 50 == 0};

    if (at_mid)
    {
	int up_score{0};
	int down_score{0};
	int right_score{0};
	int left_score{0};
	int pos_score{0};

	sf::Vector2f right{hitbox().width, 0};
	sf::Vector2f up{0, -hitbox().height};

	score_assigner(players,      up_score, down_score, right_score, left_score, pos_score, up, right);
	score_assigner(bombs,        up_score, down_score, right_score, left_score, pos_score, up, right);
	score_assigner(fires,        up_score, down_score, right_score, left_score, pos_score, up, right);
	score_assigner(powerups,     up_score, down_score, right_score, left_score, pos_score, up, right);
	score_assigner(wooden_boxes, up_score, down_score, right_score, left_score, pos_score, up, right);
	score_assigner(solid_boxes,  up_score, down_score, right_score, left_score, pos_score, up, right);

    
	if (direction.x > 0)
	{
	    right_score += rand() % 3;
	    down_score += rand() % 2;
	    up_score += rand() % 2;
	    
	}
	else if (direction.x < 0)
	{
	    left_score += rand() % 3;
	    down_score += rand() % 2;
	    up_score += rand() % 2;
	}
	else if (direction.y > 0)
	{
	    down_score += rand() % 3;
	    right_score += rand() % 2;
	    left_score += rand() % 2;
	}
	else if (direction.y < 0)
	{
	    up_score += rand() % 3;
	    right_score += rand() % 2;
	    left_score += rand() % 2;
	}
    
	pos_score -= 20;

	std::vector<std::reference_wrapper<int>> score_vec{up_score, down_score, right_score, left_score, pos_score};
	int max_score{*std::max_element(score_vec.begin(), score_vec.end())};
	
	int num_max = std::count(score_vec.begin(), score_vec.end(), max_score);

	int rand_int = rand() % num_max + 1;
	int counter{1};
        for (int i = 0; i < 4; i++)
        {
	    /*
	    std::cout << "i" << i << std::endl;
	    std::cout << score_vec[i] << std::endl;
	    std::cout << "num_max" << num_max << std::endl;
	    std::cout << "max_score" << max_score << std::endl;
	    std::cout << "rand_int" << rand_int << std::endl;
	    std::cout << "up_score" << up_score << std::endl;
	    std::cout << "down_score" << down_score << std::endl;
	    std::cout << "right_score" << right_score << std::endl;
	    std::cout << "left_score" << left_score << std::endl;
	    std::cout << "pos_score" << pos_score << std::endl;
	    std::cout << "counter" << counter << std::endl;
	    */
	    
	    if (score_vec[i] == max_score)
	    {
	        if (counter != rand_int)
	        {
		    counter += 1;
	        }
	        else if (i == 0)
	        {
		    sprite.setRotation(0);
		    sprite.move(0, -speed);
		    direction = sf::Vector2f(0, -speed);
		    break;
	        }
	        else if (i == 1)
	        {
		    sprite.setRotation(180);
		    sprite.move(0, speed);
		    direction = sf::Vector2f(0, speed);
		    break;
	        }
	        else if (i == 2)
	        {
		    sprite.setRotation(90);
                    sprite.move(speed, 0);
		    direction = sf::Vector2f(speed, 0);
		    break;
	        }
	        else if (i == 3)
	        {
	   	    sprite.setRotation(-90);
                    sprite.move(-speed, 0);
		    direction = sf::Vector2f(-speed, 0);
		    break;
	        }
		else
		{
		    direction = sf::Vector2f(0,0);
		    break;
		}
   	    }
        }
    }
    else
    {
	/*
	std::cout << "xdir" << direction.x << std::endl;
	std::cout << "ydir" << direction.y << std::endl;
	*/
        sprite.move(direction);
    }
}
