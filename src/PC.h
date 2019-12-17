#ifndef PC_H
#define PC_H
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <string>

class Pc: public Player
{
public:
    Pc(sf::Vector2f, sf::Texture &, bool,
        int, int, int, int, std::string,
        sf::Keyboard::Key,
        sf::Keyboard::Key,
        sf::Keyboard::Key,
        sf::Keyboard::Key,
        sf::Keyboard::Key);
    ~Pc() = default;
    void update(sf::Keyboard);

protected:
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
    sf::Keyboard::Key down;
    sf::Keyboard::Key up;
    sf::Keyboard::Key bomb_button;
    bool previous_bomb_button{false};
};

#endif

