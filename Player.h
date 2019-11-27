#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Bomb.h"
#include <vector>

class Bomb;
class Player: public Game_object
{
public:
    Player(sf::Vector2f pos, sf::Texture & texture, int cooldown, bool in_push,
	   int in_health, int in_speed, int in_fire, int in_cd);

    ~Player() = default;

    void new_round();
    void apply_on_hit_effect(Game_object* object) override;

    void set_push_powerup(bool var);
    bool get_push_powerup() const;

    void reduce_health(int damage);
    int get_health() const;
    bool is_dead() const;

    void increase_speed(int var);
    int get_speed() const;

    void increase_fire_size(int var);
    int get_fire_size() const;

    void increase_score(int add_score);
    int get_score() const;

    void give_bomb();
    bool is_immune() const;
    void make_immune();
    bool request_to_drop_bomb();
    Bomb* create_bomb(sf::Texture);
    

    /*testing!! remove later.
    void update(sf::Keyboard keyboard) override
    {
        if (keyboard.isKeyPressed(sf::Keyboard::Key::D))
        {
            old_position = sprite.getPosition() - sf::Vector2f(1,0);
            sprite.move(sf::Vector2f(1,0));
        }

    }
    */


protected:
    bool initial_push_powerup;
    int initial_health;
    int initial_speed;
    int initial_fire_size;
    int initial_cd;

    bool push_powerup;
    int health;
    int speed;
    int fire_size;
    int score;
    int cd;
    bool want_to_drop_bomb;

    sf::Clock immune_clock;
    std::vector<sf::Clock> bomb_cds;
    sf::Vector2f spawn_point;
};

#endif
