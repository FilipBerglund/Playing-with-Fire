#include <SFML/Graphics.hpp>
#include "State_handler.h"
#include "State.h"
#include <string>
#include <fstream>

State_handler::State_handler():
        menu_state{new Menu_state},
        game_state{new Game_state},
        end_screen{new End_screen},
        current_state{menu_state},
        width{},
        height{},
        window{},
        mouse{},
        keyboard{},
        fps_clock{},
        fps{},
        target{},
        event{},
        menu_music{}
    {
        load_window_settings();
        menu_music.openFromFile("res/menu_music.oog");
        play_music();
    }

void State_handler::run()
{
    while (window.isOpen())
    {
        fps_clock.restart();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        update();
        draw();
        window.display();
        sf::sleep (target - fps_clock.getElapsedTime());
    }
}

void State_handler::update()
{
    current_state->update(mouse, keyboard, game_state, menu_state,
                            end_screen, &current_state, window);
}

void State_handler::draw()
{
    current_state->draw(window);
}

void State_handler::play_music()
{
    menu_music.play();
}

void State_handler::load_window_settings()
{
    std::ifstream settings;
    settings.open("res/window_settings.txt");
    settings >> width;
    settings >> height;
    window.create(sf::VideoMode{width, height}, "Playing with Fire");

    settings >> fps;
    target = sf::Time{sf::milliseconds(1000 / fps)};
    settings.close();
}
