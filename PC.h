#ifndef PC
#define PC
#include "Player.h"
#include <SFML/Graphics.hpp>

class Player;
class PC: public Player
{
public:
    PC(sf::Vector2f pos, sf::Texture texture, int cooldown, int in_push,
       int in_health, int in_speed, int in_fire, int in_cd,
       sf::Keyboard::Key left_arg,
       sf::Keyboard::Key right_arg,
       sf::Keyboard::Key down_arg,
       sf::Keyboard::Key up_arg,
       sf::Keyboard::key bomb_arg);

   ~PC() = default;

    void update(sf::Keyboard keyboard);
    
protected:
    sf::Keyboard::Key left;
    sf::Keyboard::Key right:
    sf::Keyboard::Key down;
    sf::Keyboard::Key up;
    sf::Keyboard::Key bomb_button;
};

#endif

