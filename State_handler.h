#ifndef STATE_HANDLER_H
#define STATE_HANDLER_H

#include <list>
#include <SFML/Graphics.hpp>
#include "State.h"

class State_handler
{
public:
    State_handler():
    game_state{new Game_state}, menu_state{new Menu_state}, end_screen{new End_screen}
    {
        *current_state= menu_state;
    }
    void update(sf::Mouse& mouse, sf::Keyboard& keyboard, sf::RenderWindow& window)
    {
      (*current_state)->update(mouse, keyboard, game_state, menu_state,
              end_screen, current_state, window);
    }
    void draw(sf::RenderWindow& window) {(*current_state)->draw(window);}

private:
    State** current_state;
    Menu_state* menu_state;
    Game_state* game_state;
    End_screen* end_screen;

    //We get segfault without this. Any list is okay.
    std::list<int> what_is_this_help;
};
#endif
