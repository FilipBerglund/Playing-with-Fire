#include "Bomb.h"
#include "Player.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

#include <iostream>

Player::Player(sf::Vector2f pos, sf::Texture & texture,
	       bool in_push, int in_health, int in_speed, int in_fire, int in_cd, std::string in_name):
        Game_object(pos, texture),
        push_powerup{in_push},
        health{in_health},
        speed{in_speed},
        fire_size{in_fire},
        score{0},
        cd{in_cd},
        immune_clock{},
        bomb_cds{},
        spawn_point{pos},
        initial_push_powerup{in_push},
        initial_health{in_health},
        initial_speed{in_speed},
        initial_fire_size{in_fire},
        initial_cd{in_cd},
	want_to_drop_bomb{false},
	name{in_name}
{
    sf::Clock new_clock;
    bomb_cds.push_back(std::make_pair(new_clock, true));  //Listan får storlek 1.
    // sprite.setOrigin(hitbox().width/2, hitbox().height/2); //Origin blir i mitten.
}


void Player::new_round()  //Variabler återställs vid ny runda.
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


/*Spelarens applyfunktion ansvarar för vad som händer vid
  kollision med ett annat object om det är av typen Game_object.
  Game_state tar själv bort powerups vid kollision med spelare
  så spelare behöver endast hantera kollision med bomber.*/
void Player::apply_on_hit_effect(Game_object* object)
{
    /*object kommer alltid vara en bombpekare men eftersom apply
      är överlagrad från Game_object så måste vi använda
      dyanmic_cast för att behandla object som en bombpekare.
      Därmed behöver vi inte kolla om pekaren ptr nedanför
      är lika med nullptr.*/
    Bomb* ptr = dynamic_cast<Bomb*>(object);

    //TODO: Tips! Om du skriver
    //
    //if (!push_powerup)
    //  return
    //
    // ovanför denna kod skulle du kunna ta bort den första if satsen.
    // Då skulle den vara minder nästlad vilket skulle göra det
    // blir lite snyggare.
    if (abs(old_position.x - object->get_old_position().x) < 50 &&
        abs(old_position.y - object->get_old_position().y) < 50)
    {
        return;
    }
    else if (push_powerup)
    {
        /*I de stora if-satsern nedanför kollar vi först  kollision i ett visst led
          och sedan kollar vi spelarens and bombens ursprungliga positioner
          för att bestämma i vilken riktning bomben ska skjutas iväg.*/
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


bool Player::is_dead() const //Kollar om spelaren är död.
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


bool Player::request_to_drop_bomb()  //Hjälpfunktion när bomber ska droppas.
{
    if (want_to_drop_bomb)
    {
	want_to_drop_bomb = false;
        for (unsigned int i = 0; i < bomb_cds.size(); i++)  //Går igenom hela listan av klockor.
        {
            if (bomb_cds[i].first.getElapsedTime().asSeconds() >= cd || bomb_cds[i].second) //När detta uppfylls har spelaren möjligheten att droppa en bomb.
            {
		bomb_cds[i].second = false;
                bomb_cds[i].first.restart();
	        return true;
            }
	}
    }
    return false;
}

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
