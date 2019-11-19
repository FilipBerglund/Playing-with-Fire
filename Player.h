#ifndef PLAYER
#define PLAYER

#include <SFML/Graphics.hpp>
#include "Bomb.h"
#include "Powerup.h"

#include <vector>
#include <string>

class Player: public Game_object
{
public:
    Player(sf::Vector2f pos, sf::Sprite sprite):
    Game_object(pos, sprite), push_powerup{false}, health{3},
        bonus_speed{0}, fire_size{2}
    {
        sf::Clock cd;
        std::vector<sf::Clock> bomb_cds;
        bomb_cds.push_back(cd);
    }

    Bomb* drop_bomb()  //Hjälpfunktion för när bomber ska droppas. 
    {
	for (int i = 0; i < bomb_cds.size(), i++)  //Går igenom hela listan av klockor. 
	{
	    if (bomb_cds[i].getElapsedTime() >= 5) //När detta uppfylls har spelaren möjligheten att droppa en bomb. 
	    {
		bomb_cds[i].restart();  
		Bomb* ptr = new Bomb(this, fire_size);
		return ptr;
	    }
	    else if (i == bomb_cds.size())  //När detta uppfylls har spelaren inte möjligheten att droppa en bomb.
	    {
		return nullptr;
	    }
	}
    }

    bool is_dead()  //Kollar om spelaren är död.
    {
	return health <= 0;
    }

    void new_round()  //Variabler återställs vid ny runda.
    {
	push_powerup = false;
	int health = 3;
	bonus_speed = 0;
	fire_size = 0;
	bomb_cds.resize(1);
	bomb_cds[0].restart(); 
    }

    bool collision(Game_object* object) override
    {
        return object->get_hitbox().intersects(get_hitbox());
    }

    void apply(Game_object* object) override
    {
	Bomb* ptr1 = dynamic_cast<Bomb*>(object);
	Bomb* ptr2 = dynamic_cast<Powerup*>(object);

	if (ptr1 != nullptr)  
	{
	    if (push_powerup == true)  
	    {
                if (sprite.getPosition().x + sprite.getTextureRect().width/2 ==
		    ptr1->sprite.getPosition().x - ptr1->sprite.getTextureRect().width/2 &&
		    old_position.x + sprite.getTextureRect().width/2 <
		    ptr1->old_position.x - ptr1->sprite.getTextureRect().width/2)
		{
		    ptr1->glide("right");
		}
                else if(sprite.getPosition().x - sprite.getTextureRect().width/2 ==
		        ptr1->sprite.getPosition().x + ptr1->sprite.getTextureRect().width/2 &&
		        old_position.x + sprite.getTextureRect().width/2 >
		        ptr1->old_position.x - ptr1->sprite.getTextureRect().width/2)
		{
		    ptr1->glide("left");
		}
	        else if(sprite.getPosition().y - sprite.getTextureRect().height/2 ==
		        ptr1->sprite.getPosition().y + ptr1->sprite.getTextureRect().height/2 &&
		        old_position.y + sprite.getTextureRect().height/2 >
		        ptr1->old_position.y - ptr1->sprite.getTextureRect().width/2)
		{
		    ptr1->glide("up");
		}
		else 
		{
		    ptr1->glide("down");
		}	   
	    }
	    else if (ptr1->is_gliding == true)  //push_powerup == false.
	    {
		ptr1->sprite.setPosition(ptr1->old_position);
		ptr1->is_gliding == false;
	    }
	}
	else  //ptr2 != nullptr
	{
	    ptr2->remove_powerup == true;
	    //I nästa uppdate kommer Game_state ta bort powerupen från spelplanen. 
	}
    }

    void give_points(int add_score)
    {
	score += add_score;
    }

    virtual void update(sf::Keyboard keyboard) = 0;


private:
    bool push_powerup; 
    int health; 
    int bonus_speed;
    int fire_size;
    int score;
    std::vector<sf::Clock> bomb_cds;
    friend class Speed;
    friend class Extra_bomb;
    friend class Bigger_blast;
    friend class Push;
};


#endif
