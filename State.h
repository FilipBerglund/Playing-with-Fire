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
    std::string name;
private:
    virtual user_input_handler(sf::Mouse&, sf::Keyboard&) = 0;
};

class Game_state: public State
{
public:
    Game_state(): State("Game_state"),
    current_round{0}, players{}, bombs{}, fires{}, wooden_boxes{}, solid_boxes{}
    {}

    void update(sf::Mouse&, sf::Keyboard) override;
    void draw(sf::Window&) override;
    void new_game(int, int, int, int);

private:
    void check_collisions();
    void user_input_handler(sf::Mouse&, sf::Keyboard%) override;
    void new_round();
    void end_game();
    bool is_game_over();
    bool is_round_over();
    bool is_time_up();

    std::list<Player> players;
    std::list<Bomb> bombs;
    std::list<Fire> fires;
    std::list<Wooden_box> wooden_boxes;
    std::list<Solid_box> solid_boxes;

    int current_round;
    sf::Clock round_timer;
};

class Menu_state: public State
{
public:
    Menu_state(): State("Menu_state")
    {}

    void update(sf::Mouse&, sf::Keyboard&) override;
    void draw(sf::Window&) override;

private:
    void user_input_handler(sf::Mouse&, sf::Keyboard&) override;
};
#endif
