#include "Bomb.h"
#include "Player.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

#include <iostream>

Player::Player(sf::Vector2f pos, sf::Texture & texture,
        bool in_push, int in_health, int in_speed, int in_fire, int in_cd,
        std::string in_name):
        Game_object(pos, texture),
        score{0},
        push_powerup{in_push},
        health{in_health},
        speed{in_speed},
        fire_size{in_fire},
        cd{in_cd},
        want_to_drop_bomb{false},

        initial_push_powerup{in_push},
        initial_health{in_health},
        initial_speed{in_speed},
        initial_fire_size{in_fire},
        initial_cd{in_cd},

        name{in_name},

        immune_clock{},
        bomb_cds{},
        spawn_point{pos}
{
    sf::Clock new_clock;
    bomb_cds.push_back(std::make_pair(new_clock, true));  //The list of bomb clocks gets size 1.
    //The second entry of each pair is true to allow players to drop bombs immediately.
    //When the first bomb has been dropped the bool in the second entry is set to false
    //until the next round since it has served its purpose.
}


void Player::new_round()  //Resets certain parameters at the beginning of a new round.
{
    push_powerup = initial_push_powerup;
    health = initial_health;
    speed = initial_speed;
    fire_size = initial_fire_size;
    cd = initial_cd;
    want_to_drop_bomb = false;
    sprite.setPosition(spawn_point);
    bomb_cds.resize(1);
    bomb_cds[0].first.restart();
    bomb_cds[0].second = true;
}


void Player::apply_on_hit_effect(Game_object* object)  //Handles collision.
{
    //In our implementation object will always be a pointer to an instans of
    //bomb. But since we override this function from Game_object we use
    //dynamic_cast to treat object as a bomb pointer, which it will always be.
    Bomb* ptr = dynamic_cast<Bomb*>(object);

    if (abs(old_position.x - object->get_old_position().x) < 50 &&
        abs(old_position.y - object->get_old_position().y) < 50)
    {
        //If the player previously stood on the bomb then nothing happens.
        return;
    }
    //Else if the player just collided with the bomb and has a push_powerup
    //the bomb will start to glide.
    else if (push_powerup)
    {
        if (sprite.getPosition().x + hitbox().width/2 >=
            ptr->get_position().x - ptr->hitbox().width/2 &&
            old_position.x < sprite.getPosition().x)
        {
            ptr->glide("right");
        }
        else if (sprite.getPosition().x - hitbox().width/2 <=
                ptr->get_position().x + ptr->hitbox().width/2 &&
                old_position.x > sprite.getPosition().x)
        {
            ptr->glide("left");
        }
        else if (sprite.getPosition().y - hitbox().height/2 <=
                ptr->get_position().y + ptr->hitbox().height/2 &&
                old_position.y > sprite.getPosition().y)
        {
            ptr->glide("up");
        }
        else if (old_position.y < sprite.getPosition().y)
        {
            ptr->glide("down");
        }
    }
}


void Player::set_push_powerup(bool var)
{
    push_powerup = var;
}


bool Player::get_push_powerup() const
{
    return push_powerup;
}


void Player::reduce_health(int damage)
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


int Player::get_health() const
{
    return health;
}


bool Player::is_dead() const
{
    return health == 0;
}


void Player::increase_speed(int var)
{
    speed += var;
}

int Player::get_speed() const
{
    return speed;
}


void Player::increase_fire_size(int var)
{
    fire_size += var;
}

int Player::get_fire_size() const
{
    return fire_size;
}


void Player::increase_score(int add_score)
{
    score += add_score;
}


int Player::get_score() const
{
    return score;
}


void Player::give_bomb()
{
    sf::Clock new_clock;
    bomb_cds.push_back(std::make_pair(new_clock, true));
}


bool Player::is_immune() const
{
    return immune_clock.getElapsedTime().asSeconds() <= 5;
}


void Player::make_immune()
{
    immune_clock.restart();
}


//Returns true if the player can and wants to drop a bomb, else false is returned.
bool Player::request_to_drop_bomb()
{
    if (want_to_drop_bomb)
    {
        want_to_drop_bomb = false;
        //Loops through the list of clocks..
        for (uint i = 0; i < bomb_cds.size(); i++)
        {
            //If true the player can drop a bomb.
            if (bomb_cds[i].first.getElapsedTime().asSeconds() >= cd || bomb_cds[i].second)
            {
                bomb_cds[i].second = false;
                bomb_cds[i].first.restart();
                return true;
            }
        }
    }
    return false;
}

//Returns a pointer to a bomb which belongs to the player.
Bomb* Player::create_bomb(sf::Texture& bomb_texture)
{
    return new Bomb(sprite.getPosition(), bomb_texture, this, fire_size);
}

void Player::set_name(std::string new_name)
{
    name = new_name;
}

std::string Player::get_name() const
{
    return name;
}
