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
        current_state_string{menu_state->name},
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
        menu_music.play();
        menu_music.setLoop(true);
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

    if (current_state_string == menu_state->name &&
        menu_music.getPlayingOffset().asSeconds() > 21)
    {
        menu_music.setPlayingOffset(sf::seconds(0.f));
    }
    else if (current_state_string == game_state->name &&
             menu_music.getPlayingOffset().asSeconds() < 22 &&
             menu_music.getPlayingOffset().asSeconds() > 185)
    {
        menu_music.setPlayingOffset(sf::seconds(20.f));
    }
    else if (current_state_string == end_screen->name &&
            menu_music.getPlayingOffset().asSeconds() < 185)
    {
        menu_music.setPlayingOffset(sf::seconds(185.f));
    }
    current_state_string = current_state->name;
}

void State_handler::draw()
{
    current_state->draw(window);
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
