#ifndef FIRE_H
#define FIRE_H

#include <SFML/Graphics.hpp>

#include "Box.h"
#include "Game_state.h"
#include "Player.h"


class Fire: public Game_object
{
 public:
    Fire (sf::Vector2f pos, sf::Sprite sprite, int timer, int fire_size, Player*);

    bool is_boosted();
    void fire_boost(int fire_size);

    void give_points( Player owner);
    void update() override;

 private:
    Player owner();
    int timer();
    int fire_size();

    sf::Clock fire_rate;

};
#endif        
