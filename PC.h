#ifndef PC_H
#define PC_H
#include "Player.h"

class PC: public Player
{
public:
    PC(sf::Vector2f pos, sf::Texture texture, int cooldown, int in_push,
       int in_health, int in_speed, int in_fire, int in_cd,
       sf::Key left_arg, sf::Key right_arg, sf::Key down_arg, sf::Key up_arg, sf::key bomb_arg);

   ~PC() = default;

    void update(sf::Keyboard keyboard);
    
protected:
    sf::Key left;
    sf::Key right:
    sf::Key down;
    sf::Key up;
    sf::Key bomb_button;
};

#endif

