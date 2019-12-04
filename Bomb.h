#ifndef BOMB_H
#define BOMB_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Box.h"
//#include "Fire.h"
#include "Player.h"


class Bomb: public Game_object
{
 public:
    Bomb (sf::Vector2f pos, sf::Texture & texture,
     Player* player);
    //void set_owner(Player* owner, Fire fire);
    
    bool is_blasted() const;
    
    void update() override;
    
    void apply_on_hit_effect(Game_object*);
    
    void glide(std::string direction);
    
 private:
    
    bool is_gliding;
    
    // Player* owner;
    float speed;
    std::string move_direction;
    std::string direction;
    sf::Clock fuse_timer;
};
#endif
