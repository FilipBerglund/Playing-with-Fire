#ifndef POWERUP
#define POWERUP

#include <SFML/Graphics.hpp>

#include "Game_object.h"
#include "Player.h"

class Powerup: public Game_object
{
public:
    Powerup(sf::Vector2f pos, sf::Texture & texture):
    Game_object(pos, texture)
    {}

};

class Speed: public Powerup
{
public:
    Speed(sf::Vector2f pos, sf::Texture texture):
    Powerup(pos, texture)
    {}

    void apply_on_hit_effect(Game_object*) override;
};

class Bigger_blast: public Powerup
{
public:
    Bigger_blast(sf::Vector2f pos, sf::Texture texture):
    Powerup(pos, texture)
    {}

    void apply_on_hit_effect(Game_object*) override;
};

class Extra_bomb: public Powerup
{
public:
    Extra_bomb(sf::Vector2f pos, sf::Texture texture):
    Powerup(pos, texture)
    {}

    void apply_on_hit_effect(Game_object*) override;
};

class Push: public Powerup
{
public:
    Push(sf::Vector2f pos, sf::Texture texture):
    Powerup(pos, texture)
    {}

    void apply_on_hit_effect(Game_object*) override;
};
#endif
