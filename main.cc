#include <SFML/Graphics.hpp>
//#include <SFML/RenderWindow.hpp>
#include <string>
#include "State.h"
#include "State_handler.h"

int main()
{
    int const width{1280};
    int const height{720};

    sf::VideoMode mode{width, height};
    sf::RenderWindow window{mode, "Playing With Fire"};

    sf::Keyboard keyboard;
    sf::Mouse mouse;

    State_handler state_handler;
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
        state_handler.update(mouse, keyboard, window);
        state_handler.draw(window);
        window.display();
    }

    return 0;
}
