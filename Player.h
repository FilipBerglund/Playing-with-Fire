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

4. Har Game_object en konstruktor av typen Game_object(pos, sprite)
   som används nedanför?

5. Har Bomb en konstruktor av typen Bomb(Player* ptr)?

6. Hur ska vi implementera update för NPC?
*/

class Player: public Game_object
{
public:
    Player(sf::Vector2f pos, sf::Texture texture, int cooldown, int in_push,
        int in_health, int in_speed, int in_fire, int in_cd):
        Game_object(pos, texture), push_powerup{in_push}, health{in_health},
        speed{in_speed}, fire_size{in_fire}, score{0}, cd{in_cd},
        immune_clock{}, bomb_cds{}, spawn_point{pos},
        initial_push_powerup{in_push}, initial_health{in_health},
        initial_speed{in_speed}, initial_fire_size{in_fire}, initial_cd{in_cd}
    {
        sf::Clock new_clock;
        bomb_cds.push_back(new_clock);  //Listan får storlek 1.
        sprite.setOrigin(hitbox().width/2, hitbox().height/2); //Origin blir i mitten.
    }

    ~Player() = default;

    void new_round()  //Variabler återställs vid ny runda.
    {
        push_powerup = initial_push_powerup;
        health = initial_health;
        speed = initial_speed;
        fire_size = initial_fire_size;
        cd = initial_cd;
        sprite.setPosition(spawn_point);
        bomb_cds.resize(1);
        bomb_cds[0].restart();
    }

    /*Spelarens applyfunktion ansvarar för vad som händer vid
      kollision med ett annat object om det är av typen Game_object.
      Game_state tar själv bort powerups vid kollision med spelare
      så spelare behöver endast hantera kollision med bomber.*/
    void apply_on_hit_effect(Game_object* object) override
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
            if (sprite.getPosition().x + hitbox().width/2 >=
                ptr->sprite.getPosition().x - ptr->hitbox().width/2 &&
                old_position.x + hitbox().width/2 <
                ptr->old_position.x - hitbox().width/2)
            {
                ptr->glide("right");
            }
            else if(sprite.getPosition().x - hitbox().width/2 <=
                ptr->sprite.getPosition().x + ptr->hitbox().width/2 &&
                old_position.x + hitbox().width/2 >
                ptr->old_position.x - ptr->hitbox().width/2)
            {
                ptr->glide("left");
            }
            else if(sprite.getPosition().y - hitbox().height/2 <=
                ptr->sprite.getPosition().y + ptr->hitbox().height/2 &&
                old_position.y + hitbox().height/2 >
                ptr->old_position.y - ptr->hitbox().width/2)
            {
                ptr->glide("up");
            }
            else  // If-sats ej nödvändig p.g.a. uteslutning.
            {
                ptr->glide("down");
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

    void increase_speed(int var)
    {
        speed += var;
    }

    int get_speed()
    {
        return speed;
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

    int get_score()
    {
        return score;
    }

    void give_bomb()
    {
        sf::Clock new_clock;
        bomb_cds.push_back(new_clock);
    }

    bool is_immune()
    {
        return immune_clock.getElapsedTime().asSeconds() <= 5;
    }

    void make_immune()
    {
        immune_clock.restart();
    }

    Bomb* drop_bomb()  //Hjälpfunktion när bomber ska droppas.
    {
        for (int i = 0; i < bomb_cds.size(); i++)  //Går igenom hela listan av klockor.
        {
            if (bomb_cds[i].getElapsedTime().asSeconds() >= cd) //När detta uppfylls har spelaren möjligheten att droppa en bomb.
            {
                bomb_cds[i].restart();
                Bomb* ptr = new Bomb(this);
                return ptr;
            }
        }
        return nullptr;  // Player kan inte droppa en bomb.
    }

    virtual void update(sf::Keyboard); //update för PC.

    //update för NPC?
protected:
    bool push_powerup;
    int health;
    int speed;
    int fire_size;
    int score;
    int cd;
    sf::Clock immune_clock;
    std::vector<sf::Clock> bomb_cds;
    sf::Vector2f spawn_point;
    bool initial_push_powerup;
    int initial_health;
    int initial_speed;
    int initial_fire_size;
    int initial_cd;
};

#endif
