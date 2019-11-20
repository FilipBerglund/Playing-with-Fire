#ifndef BOX
#define BOX

#include <SFML/Graphics.hpp>
#include "Game_object.h"


class Box: public Game_object
{
public:
    Box(sf::Vector2f pos, sf::Texture texture):
    Game_object(pos, texture) {}
};


class Solid_box: public Box
{
public:
    Solid_box(sf::Vector2f pos, sf::Texture texture):
    Box(pos, texture) {}

    void collision() {}
};


class Wooden_box: public Box
{
public:
    Wooden_box(sf::Vector2f pos, sf::Texture texture):
    Box(pos, texture), health{0} {}

    void collision() {}
    bool is_dead() const
    {
        return health == 0 ? true : false;
    }

private:
    uint health;
};
#endif
