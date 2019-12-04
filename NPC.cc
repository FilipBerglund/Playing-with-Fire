#include <Player.h>
#include "Bomb.h"
#include "Fire.h"
#include "Solid_box.h"
#include "Wooden_box.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <functional>

NPC::NPC(sf::Vector2f pos, sf::Texture & texture, int cooldown, bool in_push,
         int in_health, int in_speed, int in_fire, int in_cd, std::string in_name):
    Player(pos, texture, cooldown, in_push, in_health, in_speed, in_fire, in_cd, in_name)
{}

int NPC::local_score(std::string object) const
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
	return 1;
    }
    return 0;
}

void NPC::score_assigner(list<Game_object*>& objects, int& up, int& down, int& right, int& left, int& pos
			 sf::Vector2f up, sf::Vector2f right, std::string type) const
{
    for (Game_object * object : objects)
    {
	if (object->hitbox().contains(position + up))
	{
	    up += local_score(type)
	}
	if (object->hitbox().contains(position - up))
	{
	    down += local_score(type);
	}
	if (object->hitbox().contains(position + right))
	{
	    right += local_score(type);
	}
	if (object->hitbox().contains(position - right))
	{
	    left += local_score(type);
	}
	if (object->hitbox().contains(position))
	{
	    pos += local_score(type);
	}
    }
}

void NPC::update(std::list<Players*>& players, std::list<Bomb*>& bombs, list<Fire*>& fires
		 std::list<Powerup*>& powerups, std::list<Wooden_box*>& wooden_boxes, std::list<Solid_box*>& solid_boxes)
{
    int up_score{0};
    int down_score{0};
    int right_score{0};
    int left_score{0};
    int pos_score{0};
    sf::Vector2f right{hitbox().width, 0};
    sf::Vector2f up{0, -hitbox().height};

    score_assigner(players, up_score, down_score, right_score, left_score, up, down, "player");
    score_assigner(bombs, up_score, down_score, right_score, left_score, up, down, "bomb");
    score_assigner(fires, up_score, down_score, right_score, left_score, up, down, "fire");
    score_assigner(powerups, up_score, down_score, right_score, left_score, up, down, "powerup");
    score_assigner(wooden_boxes, up_score, down_score, right_score, left_score, 0.51*up, 0.51*down, "box");
    score_assigner(solid_boxes, up_score, down_score, right_score, left_score, 0.51*up, 0.51*down, "box");

    std::vector<std::reference_wrapper<int>> vec{up_score, down_score, right_score, left_score};
    int max_score{*std::max_element(v.begin(), v.end())};
}
