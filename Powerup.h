#ifndef POWERUP
#define POWERUP

#include <SFML/Graphics.hpp>

#include "Game_object.h"
#include "Player.h"

class Powerup: public Game_object
{
public:
    Powerup(sf::Vector2f pos, sf::Sprite sprite):
    Game_object(pos, sprite)
    {}

    virtual void apply(Player) = 0;
    virtual void update() = 0;
};

class Speed: public Powerup
{
public:
    Speed(sf::Vector2f pos, sf::Sprite sprite):
    Powerup(pos, sprite)
    {}

    void apply(Player) override;
    void update() override;
};

class Bigger_blast: public Powerup
{
public:
    Bigger_blast(sf::Vector2f pos, sf::Sprite sprite):
    Powerup(pos, sprite)
    {}

    void apply(Player) override;
    void update() override;
};

class Extra_bomb: public Powerup
{
public:
    Extra_bomb(sf::Vector2f pos, sf::Sprite sprite):
    Powerup(pos, sprite)
    {}

    void apply(Player) override;
    void update() override;
};

class Push: public Powerup
{
public:
    Push(sf::Vector2f pos, sf::Sprite sprite):
    Powerup(pos, sprite)
    {}

    void apply(Player) override;
    void update() override;
};
#endif
