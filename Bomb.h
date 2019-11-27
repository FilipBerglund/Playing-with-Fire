#ifndef BOMB_H
#define BOMB_H

#include <SFML/Graphics.hpp>
#include "Box.h"
#include "Fire.h"
#include "Player.h"
#include "Game_state.h"


class Bomb: public Game_object
{
 public:
    Bomb (sf::Vector2f pos, sf::Texture texture,
     Player* player);
    void spawn_fire(Player* owner, float timer, Fire fire);
    void update() override;

    //void collision (Game_object*);
    void apply_on_hit_effect(Game_object*);

    void glide(std::string direction);
    bool is_gliding() const;
    void set_is_gliding(bool sam);

 private:
    Player* owner;
    float timer;

    sf::Clock ticking_bomb; 

};
#endif