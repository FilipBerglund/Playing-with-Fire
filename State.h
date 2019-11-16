#ifndef STATE
#define STATE

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Powerup.h"
#include "Box.h"

#include <string>
#include <list>

class State
{
public:
    State(std::string n): name{n}
    {}

    virtual void update(sf::Mouse&, sf::Keyboard&) = 0;
    virtual void draw(sf::Window&) = 0;
private:
    std::string name;
    virtual user_input_handler(sf::Mouse&, sf::Keyboard&) = 0;
};

class Game_state: public State
{
public:
    Game_state(): State("Game_state")
    {}

    void update(sf::Mouse&, sf::Keyboard) override;
    void draw(sf::Window&) override;

private:
    void user_input_handler(sf::Mouse&, sf::Keyboard%) override;
    std::list<Player> players;
//    std::list<Bomb> bombs;
//    std::list<Fire> fires;
    std::list<Wooden_box> wooden_boxes;
    std::list<Solid_box> solid_boxes;

};

class Menu_state: public State
{
public:
    Game_state(): State("Game_state")
    {}

    void update(sf::Mouse&, sf::Keyboard) override;
    void draw(sf::Window&) override;

private:
    void user_input_handler(sf::Mouse&, sf::Keyboard%) override;
};
#endif
