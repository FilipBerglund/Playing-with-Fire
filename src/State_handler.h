#ifndef STATE_HANDLER_H
#define STATE_HANDLER_H

#include <SFML/Graphics.hpp>
#include "State.h"

class State_handler
{
public:
    State_handler();
    State_handler(const State_handler&) = delete;
    State_handler& operator=(const State_handler&) = delete;

    void update();
    void draw();
    void load_window_settings();
    void run();

private:
    Menu_state* menu_state;
    Game_state* game_state;
    End_screen* end_screen;
    State* current_state;
    uint width;
    uint height;
    sf::RenderWindow window;
    sf::Mouse mouse;
    sf::Keyboard keyboard;
    sf::Clock fps_clock;
    double fps;
    sf::Time target;
    sf::Event event;
};
#endif
