#ifndef PLAYER
#define PLAYER

#include <SFML/Graphics.hpp>
#include "Game_object.h"
#include <vector>

class Player: public Game_object
{
public:
    Player(sf::Vector2f pos, sf::Sprite sprite):
    Game_object(pos, sprite), push_powerup{false}, health{3},
        bonus_speed{0}, fire_size{2}
    {
        sf::Clock cd;
        std::vector<sf::Clock> bomb_cds;
        bomb_cds.push_back(cd);
    }

private:
    bool push_powerup;
    uint health;
    uint bonus_speed;
    uint fire_size;
    std::vector<sf::Clock> bomb_cds;
    friend class Speed;
    friend class Extra_bomb;
    friend class Bigger_blast;
    friend class Push;
};


#endif
