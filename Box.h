#ifndef BOX
#define BOX

#include <SFML/Graphics.hpp>
#include "Game_object.h"


class Box: public Game_object
{
public:
    Box(sf::Vector2f pos, sf::Texture & texture):
    Game_object(pos, texture) {}
};


class Solid_box: public Box
{
public:
    Solid_box(sf::Vector2f pos, sf::Texture & texture):
    Box(pos, texture) {}

    void apply_on_hit_effect(Game_object* object) override
    {
        object->undo_last_move();
    }
};


class Wooden_box: public Box
{
public:
    Wooden_box(sf::Vector2f pos, sf::Texture & texture):
    Box(pos, texture), health{1} {}

    void apply_on_hit_effect(Game_object* object) override
    {
        object->undo_last_move();
    }
    bool is_dead() const
    {
        return health == 0 ? true : false;
    }

private:
    uint health;
};
#endif
