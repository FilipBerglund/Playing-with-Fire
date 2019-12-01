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
    
    void glide();
    
 private:
    
    bool is_gliding;
<<<<<<< HEAD
    // Player* owner;
=======
    //Player* owner;
>>>>>>> bd635c11a85d8f78a01ec13f6db69359cc0d60db
    float speed;
    std::string direction;
    sf::Clock fuse_timer;
};
#endif
