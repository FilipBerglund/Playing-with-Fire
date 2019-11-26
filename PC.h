#ifndef PC_H
#define PC_H
#include <SFML/Graphics.hpp>
#include "Player.h"

class Pc: public Player
{
public:
    Pc(sf::Vector2f, sf::Texture, int, bool,
       int, int, int, int,
       sf::Keyboard::Key,
       sf::Keyboard::Key,
       sf::Keyboard::Key,
       sf::Keyboard::Key,
       sf::Keyboard::Key);

    void update(sf::Keyboard) override;

protected:
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
    sf::Keyboard::Key down;
    sf::Keyboard::Key up;
    sf::Keyboard::Key bomb_button;
};

#endif

