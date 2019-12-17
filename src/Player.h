#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Bomb.h"
#include <vector>
#include <string>
#include <utility>

class Bomb;  //Bomb depends on Player and vice versa, this line solves the problem.
class Player: public Game_object
{
public:
    Player(sf::Vector2f pos, sf::Texture & texture, bool in_push,
	   int in_health, int in_speed, int in_fire, int in_cd, std::string in_name);

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
    Bomb* create_bomb(sf::Texture&);

    void set_name(std::string);
    std::string get_name() const;

protected:
    int score;
    bool push_powerup;
    int health;
    int speed;
    int fire_size;
    int cd;
    bool want_to_drop_bomb;

    bool initial_push_powerup;
    int initial_health;
    int initial_speed;
    int initial_fire_size;
    int initial_cd;


    std::string name;

    sf::Clock immune_clock;
    std::vector<std::pair<sf::Clock, bool>> bomb_cds;
    sf::Vector2f spawn_point;
};

#endif
