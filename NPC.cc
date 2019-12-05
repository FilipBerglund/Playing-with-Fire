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

Npc::Npc(sf::Vector2f pos, sf::Texture & texture, int cooldown, bool in_push,
         int in_health, int in_speed, int in_fire, int in_cd, std::string in_name):
    Player(pos, texture, cooldown, in_push, in_health, in_speed, in_fire, in_cd, in_name)
{}

int Npc::local_score(std::string object) const
{
    if (object == "box")
    {
	return -20;
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
	return 2;
    }
    return 0;
}

void Npc::score_assigner(std::list<Bomb*>& objects, int& up_score, int& down_score, int& right_score,
			 int& left_score, int& pos_score, sf::Vector2f up, sf::Vector2f right, std::string type) const
{
    for (Game_object * object : objects)
    {
	if (object->hitbox().contains(sprite.getPosition() + up))
	{
	    up_score += local_score(type);
	}
	if (object->hitbox().contains(sprite.getPosition() - up))
	{
	    down_score += local_score(type);
	}
	if (object->hitbox().contains(sprite.getPosition() + right))
	{
	    right_score += local_score(type);
	}
	if (object->hitbox().contains(sprite.getPosition() - right))
	{
	    left_score += local_score(type);
	}
	if (object->hitbox().contains(sprite.getPosition()))
	{
	    pos_score += local_score(type);
	}
    }
}

void Npc::score_assigner(std::list<Fire*>& objects, int& up_score, int& down_score, int& right_score,
			 int& left_score, int& pos_score, sf::Vector2f up, sf::Vector2f right, std::string type) const
{
    for (Game_object * object : objects)
    {
	if (object->hitbox().contains(sprite.getPosition() + up))
	{
	    up_score += local_score(type);
	}
	if (object->hitbox().contains(sprite.getPosition() - up))
	{
	    down_score += local_score(type);
	}
	if (object->hitbox().contains(sprite.getPosition() + right))
	{
	    right_score += local_score(type);
	}
	if (object->hitbox().contains(sprite.getPosition() - right))
	{
	    left_score += local_score(type);
	}
	if (object->hitbox().contains(sprite.getPosition()))
	{
	    pos_score += local_score(type);
	}
    }
}

void Npc::score_assigner(std::list<Powerup*>& objects, int& up_score, int& down_score, int& right_score,
			 int& left_score, int& pos_score, sf::Vector2f up, sf::Vector2f right, std::string type) const
{
    for (Game_object * object : objects)
    {
	if (object->hitbox().contains(sprite.getPosition() + up))
	{
	    up_score += local_score(type);
	}
	if (object->hitbox().contains(sprite.getPosition() - up))
	{
	    down_score += local_score(type);
	}
	if (object->hitbox().contains(sprite.getPosition() + right))
	{
	    right_score += local_score(type);
	}
	if (object->hitbox().contains(sprite.getPosition() - right))
	{
	    left_score += local_score(type);
	}
	if (object->hitbox().contains(sprite.getPosition()))
	{
	    pos_score += local_score(type);
	}
    }
}

void Npc::score_assigner(std::list<Wooden_box*>& objects, int& up_score, int& down_score, int& right_score,
			 int& left_score, int& pos_score, sf::Vector2f up, sf::Vector2f right, std::string type) const
{
    for (Game_object * object : objects)
    {
	if (object->hitbox().contains(sprite.getPosition() + up))
	{
	    up_score += local_score(type);
	}
	if (object->hitbox().contains(sprite.getPosition() - up))
	{
	    down_score += local_score(type);
	}
	if (object->hitbox().contains(sprite.getPosition() + right))
	{
	    right_score += local_score(type);
	}
	if (object->hitbox().contains(sprite.getPosition() - right))
	{
	    left_score += local_score(type);
	}
	if (object->hitbox().contains(sprite.getPosition()))
	{
	    pos_score += local_score(type);
	}
    }
}

void Npc::score_assigner(std::list<Solid_box*>& objects, int& up_score, int& down_score, int& right_score,
			 int& left_score, int& pos_score, sf::Vector2f up, sf::Vector2f right, std::string type) const
{
    for (Game_object * object : objects)
    {
	if (object->hitbox().contains(sprite.getPosition() + up))
	{
	    up_score += local_score(type);
	}
	if (object->hitbox().contains(sprite.getPosition() - up))
	{
	    down_score += local_score(type);
	}
	if (object->hitbox().contains(sprite.getPosition() + right))
	{
	    right_score += local_score(type);
	}
	if (object->hitbox().contains(sprite.getPosition() - right))
	{
	    left_score += local_score(type);
	}
	if (object->hitbox().contains(sprite.getPosition()))
	{
	    pos_score += local_score(type);
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
	if (cond1 || cond2 || cond3 || cond4 || cond5)
	{
	    if (player != this)
	    {
		want_to_drop_bomb = true;
	    }
	    if (cond1)
	    {
	        up_score += local_score("player");
		want_to_drop_bomb = true;
	    }
            if (cond2)
            {
	        down_score += local_score("player");
		want_to_drop_bomb = true;
	    }
	    if (cond3)
	    {
	        right_score += local_score("player");
		want_to_drop_bomb = true;
	    }
	    if (cond4)
	    {
	        left_score += local_score("player");
		want_to_drop_bomb = true;
	    }
            if (cond5)
            {
	        pos_score += local_score("player");
		want_to_drop_bomb = true;
	    }
	}
    }
}

void Npc::update(std::list<Player*>& players, std::list<Bomb*>& bombs, std::list<Fire*>& fires,
		 std::list<Powerup*>& powerups, std::list<Wooden_box*>& wooden_boxes, std::list<Solid_box*>& solid_boxes)
{
    int up_score{0};
    int down_score{0};
    int right_score{0};
    int left_score{0};
    int pos_score{0};
    sf::Vector2f right{hitbox().width, 0};
    sf::Vector2f up{0, -hitbox().height};

    score_assigner(players,      up_score, down_score, right_score, left_score, pos_score, up, right);
    score_assigner(bombs,        up_score, down_score, right_score, left_score, pos_score, up, right, "bomb");
    score_assigner(fires,        up_score, down_score, right_score, left_score, pos_score, up, right, "fire");
    score_assigner(powerups,     up_score, down_score, right_score, left_score, pos_score, up, right, "powerup");
    score_assigner(wooden_boxes, up_score, down_score, right_score, left_score, pos_score, up, right, "box");
    score_assigner(solid_boxes,  up_score, down_score, right_score, left_score, pos_score, up, right, "box");

    pos_score -= 10;
    std::vector<std::reference_wrapper<int>> score_vec{up_score, down_score, right_score, left_score, pos_score};
    int max_score{*std::max_element(score_vec.begin(), score_vec.end())};
    int num_max = std::count(score_vec.begin(), score_vec.end(), max_score);

    srand (time(NULL));
    int rand_int = rand() % num_max + 1;
    int counter{1};
    
    for (int i = 0; i < 5; i++)
    {
	if (score_vec[i] == max_score)
	{
	    if (counter != rand_int)
	    {
		counter += 1;
	    }
	    else if (i == 0 && counter == rand_int)
	    {
		sprite.setRotation(0);
		sprite.move(0, -speed);
	    }
	    else if (i == 1 && counter == rand_int)
	    {
		sprite.setRotation(180);
		sprite.move(0, speed);
	    }
	    else if (i == 2 && counter == rand_int)
	    {
		sprite.setRotation(90);
                sprite.move(speed, 0);
	    }
	    else if (i == 3 && counter == rand_int)
	    {
		sprite.setRotation(-90);
                sprite.move(-speed, 0);
	    }
	}
    }
}
