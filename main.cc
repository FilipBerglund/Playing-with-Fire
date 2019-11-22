#include <SFML/Graphics.hpp>
//#include <SFML/RenderWindow.hpp>
#include <string>

int main()
{
    int const width{1280};
    int const height{720};

    sf::VideoMode mode{width, height};
    sf::RenderWindow window{mode, "Playing With Fire"};

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
    }

    return 0;
}
