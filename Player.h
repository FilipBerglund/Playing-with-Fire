#ifndef PLAYER
#define PLAYER

#include <SFML/Graphics.hpp>
#include "Bomb.h"
#include "Powerup.h"
#include <vector>
#include <string>
#include <iostream>

/*
Saker som ej är klara eller otydliga

1. Behöver vi alla includes ovanför eller följer vissa från Game_object?

2. Har funktionerna bool is_gliding(), void set_is_gliding(bool) 
   och void gliding(string) implementerats i Bomb?

3. När en spelare blir skadad så blir spelaren immun mot
   skada i 5 sekunder. Är detta en lämplig siffra?

4. Ska fire_size inledningsvis har värdet 2?

5. Har Game_object en konstruktor av typen Game_object(pos, old_pos, sprite)
   som används nedanför? 

6. Har Bomb en konstruktor av Bomb(Player* ptr, int fire_size)?

7. Hur ska vi implementera update för NPC? 
*/

class Player: public Game_object
{
public:
    Player(sf::Vector2f pos, sf::Vector2f old_pos, sf::Sprite sprite, int bombcd):
	Game_object(pos, old_pos, sprite), push_powerup{false}, health{3},
        bonus_speed{0}, fire_size{2}, score{0}, immune_clock{}, bomb_cds{}, bomb_cd{bombcd}
    {
        bomb_cds.push_back();  //Listan får storlek 1.
	sprite.setOrigin(sprite->getTextureRect.width/2, sprite->getTextureRect.height/2) //Origin blir i mitten.
    }

    ~Player() = default;

    void new_round(int initial_push, int initial_health, int initial_bonus_speed, int initial_fire_size)  //Variabler återställs vid ny runda.
    {
	push_powerup = initial_push;
	int health = initial_health;
	bonus_speed = initial_bonus_speed;
	fire_size = initial_fire_size;
	bomb_cds.resize(1);
	bomb_cds[0].restart(); 
    }

    bool collision(Game_object* object) override
    {
        return object->hit_box().intersects(hit_box());
    }

    /*Spelarens applyfunktion ansvarar för vad som händer vid
      kollision med ett annat object om det är av typen Game_object.
      Game_state tar själv bort powerups vid kollision med spelare
      så spelare behöver endast hantera kollision med bomber.*/ 
    void apply(Game_object* object) override
    {
	/*object kommer alltid vara en bombpekare men eftersom apply
	  är överlagrad från Game_object så måste vi använda
	  dyanmic_cast för att behandla object som en bombpekare.
	  Därmed behöver vi inte kolla om pekaren ptr nedanför
	  är lika med nullptr.*/ 
	Bomb* ptr = dynamic_cast<Bomb*>(object);
	
	if (push_powerup == true)  
	{ 	    
	    /*I de stora if-satsern nedanför kollar vi först  kollision i ett visst led
	      och sedan kollar vi spelarens and bombens ursprungliga positioner
	      för att bestämma i vilken riktning bomben ska skjutas iväg.*/ 
            if (sprite.getPosition().x + sprite.getTextureRect().width/2 >=                
		ptr->sprite.getPosition().x - ptr->sprite.getTextureRect().width / 2 &&   
		old_position.x + sprite.getTextureRect().width/2 <
		ptr->old_position.x - ptr->sprite.getTextureRect().width/2)
	    {
		ptr->glide("right");
	    }
            else if(sprite.getPosition().x - sprite.getTextureRect().width/2 <=
		    ptr->sprite.getPosition().x + ptr->sprite.getTextureRect().width/2 &&
	            old_position.x + sprite.getTextureRect().width/2 >
	            ptr->old_position.x - ptr->sprite.getTextureRect().width/2)
	    {
	        ptr1->glide("left");
	    }
	    else if(sprite.getPosition().y - sprite.getTextureRect().height/2 <=
	            ptr->sprite.getPosition().y + ptr->sprite.getTextureRect().height/2 &&
       	            old_position.y + sprite.getTextureRect().height/2 >
		    ptr->old_position.y - ptr->sprite.getTextureRect().width/2)
	    {
	        ptr1->glide("up");
	    }
	    else  // If-sats ej nödvändig p.g.a. uteslutning. 
	    {
		ptr1->glide("down");
	    }	   
	}
        else if (ptr->is_gliding() == true)  //push_powerup == false så bomben ska stanna.
        {
	    ptr->sprite.setPosition(ptr->old_position);
	    ptr->set_is_gliding(false);
	}
    }

    void set_push_powerup(bool var)
    {
	push_powerup = var;
    }

    bool get_push_powerup()
    {
	return push_powerup;
    }

    void reduce_health(int damage)
    {
	if (health - damage <= 0)
	{
	    health = 0;
	}
	else
	{
	    health -= damage;
	}
    }

    int get_health()
    {
	return health;
    }

    bool is_dead()  //Kollar om spelaren är död.
    {
	return health == 0;
    }

    void increase_bonus_speed(int var)
    {
	bonus_speed += var;
    }

    int get_bonus_speed()
    {
	return bonus_speed;
    }

    void increase_fire_size(int var)
    {
	fire_size += var;
    }

    int get_fire_size()
    {
	return fire_size;
    }

    void increase_score(int add_score)
    {
	score += add_score;
    }

    void get_score()
    {
	return score;
    }

    void increase_bombs()
    {
	bomb_cds.push_back(); 
    }

    bool is_immune()
    {
	return immune_clock.getElapsedTime() <= 5;
    }

    void make_immune()
    {
	immune_clock.restart();
    }

    Bomb* drop_bomb()  //Hjälpfunktion när bomber ska droppas. 
    {
	for (int i = 0; i < bomb_cds.size(), i++)  //Går igenom hela listan av klockor. 
	{
	    if (bomb_cds[i].getElapsedTime() >= bomb_cd) //När detta uppfylls har spelaren möjligheten att droppa en bomb. 
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

    const sf::IntRect & hit_box() override
    {
	return sprite.getTextureRect();
    }

    virtual void update(sf::Keyboard) = 0;

    //update för NPC?
private:
    bool push_powerup; 
    int health; 
    int bonus_speed;
    int fire_size;
    int score;
    int bomb_cd;
    sf::Clock immune_clock;
    std::vector<sf::Clock> bomb_cds;
    
    friend class Speed;
    friend class Extra_bomb;
    friend class Bigger_blast;
    friend class Push;
};

#endif
