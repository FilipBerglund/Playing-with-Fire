#ifndef BOMB_H
#define BOMB_H

#include "Game_object.h"
#include "Player.h"

class Player;
class Bomb: public Game_object
{
public:
    Bomb(sf::Vector2f, sf::Texture, Player*);
    void apply_on_hit_effect(Game_object*) {}
private:
    Player* owner;
};
#endif
