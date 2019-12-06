#include <SFML/Graphics.hpp>
//#include <SFML/RenderWindow.hpp>
#include <string>
#include "State.h"
#include <random>

int main()
{
	/*
    std::random_device rd;
    std::mt19937 mt{rd()};
    std::uniform_int_distribution<int> dist(0, 9);
    */
    srand(123);
    int const width{1280};
    int const height{720};

    sf::VideoMode mode{width, height};
    sf::RenderWindow window{mode, "Playing With Fire"};

    sf::Keyboard keyboard;
    sf::Mouse mouse;

    Game_state game_state;
    game_state.new_game(1,0,0,0);
    
    sf::Clock fps_clock;
    double const fps{144.0};
    sf::Time const target {sf::milliseconds(1000.0 / fps)};
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
        game_state.update(mouse, keyboard);
        game_state.draw(window);
        window.display();
	
	sf::sleep (target - fps_clock.getElapsedTime());
    }

    return 0;
}
