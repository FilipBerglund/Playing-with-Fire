#ifndef STATE_HANDLER_H
#define STATE_HANDLER_H

#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include "State.h"

class State_handler
{
public:
    State_handler():
        menu_state{new Menu_state},
        game_state{new Game_state},
        end_screen{new End_screen}
    {
        *current_state = menu_state;
    }
    State_handler(const State_handler&) = delete;
    State_handler operator=(const State_handler&) = delete;

    void update(sf::Mouse& mouse, sf::Keyboard& keyboard, sf::RenderWindow& window)
    {
      (*current_state)->update(mouse, keyboard, game_state,
                               menu_state, end_screen, current_state, window);
    }
    void draw(sf::RenderWindow& window) {(*current_state)->draw(window);}

private:
    Menu_state* menu_state;
    Game_state* game_state;
    End_screen* end_screen;
    State** current_state;
};
#endif
