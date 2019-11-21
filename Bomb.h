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
    Bomb (sf::Vector2f pos, sf::Sprite sprite, Player*);
    void spawn_fire(Player* owner, int timer, Fire fire);
    void update() override;

    void collision (Game_object* object);

    void glide(std::string direction);
    bool is_gliding() const;
    void set_is_gliding(bool sam);

 private:
    std::string direction();
    Player* owner();
    int timer();

    sf::Clock ticking_bomb; 

};
#endif