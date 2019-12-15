#include <SFML/Graphics.hpp>
//#include <SFML/RenderWindow.hpp>
#include <string>
#include "State.h"
#include <random>
#include "State_handler.h"

int main()
{
	/*
    std::random_device rd;
    std::mt19937 mt{rd()};
    std::uniform_int_distribution<int> dist(0, 9);
    */
    srand(time(NULL));
    int const width{1280};
    int const height{720};

    sf::VideoMode mode{width, height};
    sf::RenderWindow window{mode, "Playing With Fire"};

    sf::Keyboard keyboard;
    sf::Mouse mouse;

    sf::Clock fps_clock;
    double const fps{144.0};
    sf::Time const target {sf::milliseconds(1000.0 / fps)};
    State_handler state_handler;
    while (window.isOpen())
    {
        fps_clock.restart();
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
	
	sf::sleep (target - fps_clock.getElapsedTime());
    }

    return 0;
}
