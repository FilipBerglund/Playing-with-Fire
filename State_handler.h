#ifndef STATE_HANDLER
#define STATE_HANDLER

#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include "State.h"

class State_handler
{
public:
    State_handler():
  game_state{new Game_state}, menu_state{new Menu_state}, end_screen{new End_screen}
    {
    	game_state->new_game(1,0,0,0);
        current_state=end_screen;
    }
    void update(sf::Mouse& mouse, sf::Keyboard& keyboard)
    {
        current_state->update(mouse, keyboard, game_state, menu_state, end_screen, current_state);
	 
    }
    void draw(sf::RenderWindow& window) {current_state->draw(window);}

private:
    State* current_state;
    Menu_state* menu_state;
    Game_state* game_state;
    End_screen* end_screen;

    std::string current_state_string;
    std::list<State*> states;
};
/*
void State_handler::change_state()
{
    if (!(current_state->name == current_state_string))
        for (State* state: states)
        {
            if (state->name == current_state_string)
            {
                current_state = state;
            }
        }
}
*/
#endif
