#include <SFML/Graphics.hpp>
//#include <SFML/RenderWindow.hpp>
#include <string>
#include "State.h"

int main()
{
    int const width{1280};
    int const height{720};

    sf::VideoMode mode{width, height};
    sf::RenderWindow window{mode, "Playing With Fire"};

    sf::Keyboard keyboard;
    sf::Mouse mouse;

    Game_state game_state;
    game_state.new_game(1,0,0,0);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
        }
        window.clear();
        game_state.update(mouse, keyboard);
        game_state.draw(window);
        window.display();
    }

    return 0;
}
