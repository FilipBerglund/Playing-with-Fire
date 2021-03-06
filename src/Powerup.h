#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>

#include "Game_object.h"
#include "Player.h"

class Powerup: public Game_object
{
public:
    Powerup(sf::Vector2f pos, sf::Texture& texture):
            Game_object(pos, texture)
    {}
    ~Powerup() = default;
};

class Speed: public Powerup
{
public:
    Speed(sf::Vector2f pos, sf::Texture& texture):
            Powerup(pos, texture)
    {}
    ~Speed() = default;

    void apply_on_hit_effect(Game_object*) override;
};

class Bigger_blast: public Powerup
{
public:
    Bigger_blast(sf::Vector2f pos, sf::Texture& texture):
            Powerup(pos, texture)
    {}
    ~Bigger_blast() = default;

    void apply_on_hit_effect(Game_object*) override;
};

class Extra_bomb: public Powerup
{
public:
    Extra_bomb(sf::Vector2f pos, sf::Texture& texture):
            Powerup(pos, texture)
    {}
    ~Extra_bomb() = default;

    void apply_on_hit_effect(Game_object*) override;
};

class Push: public Powerup
{
public:
    Push(sf::Vector2f pos, sf::Texture& texture):
            Powerup(pos, texture)
    {}
    ~Push() = default;

    void apply_on_hit_effect(Game_object*) override;
};
#endif
