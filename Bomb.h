#ifndef BOMB_H
#define BOMB_H

#include <SFML/Graphics.hpp>
#include "Game_object.h"
#include <string>

class Player;
class Bomb: public Game_object
{
public:
    Bomb(sf::Vector2f, sf::Texture&, Player*);
    void apply_on_hit_effect(Game_object*) {}
    void glide(std::string) {};
    bool is_gliding() {return false;}
private:
    Player* owner;
};
#endif
