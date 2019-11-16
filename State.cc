#include "State.h"
#include <SFML/Graphics.hpp>

void Game_state::update(sf::Mouse mouse, sf::Keyboard keyboard)
{
    user_input_handler(mouse, keyboard);
    for (Player& player : Players)
    {
        player.update(keyboard);
    }


}
