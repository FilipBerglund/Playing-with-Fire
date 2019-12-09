#ifndef BOMB_H
#define BOMB_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Box.h"
#include "Player.h"
#include "Game_object.h"

class Player;
class Bomb: public Game_object
{
public:
    Bomb(sf::Vector2f pos, sf::Texture & texture,
    Player* player);

    ~Bomb();
    
    bool is_blasted() const;
    void update();
    void apply_on_hit_effect(Game_object*);
    void glide(std::string);
    Player* get_owner() const;
    sf::Vector2f get_position() const;
    
private:    
    bool is_gliding;
    Player* owner;
    int speed;
    std::string move_direction;
    sf::Clock fuse_timer;
};
#endif
