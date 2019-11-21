#ifndef STATE
#define STATE

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Powerup.h"
#include "Box.h"
#include "Bomb.h"
#include "Fire.h"

#include <string>
#include <list>

class State
{
public:
    State(std::string n): name{n}
    {}

    virtual void update(sf::Mouse&, sf::Keyboard&) = 0;
    virtual void draw(sf::RenderWindow&) = 0;
    std::string name;
private:
    virtual void user_input_handler(sf::Mouse&, sf::Keyboard&) = 0;
    virtual void load_textures() = 0;
};

class Game_state: public State
{
public:
    Game_state();

    void update(sf::Mouse&, sf::Keyboard&) override;
    void draw(sf::RenderWindow&) override;
    void new_game(int, int, int, int);

private:
    void check_collisions();
    void user_input_handler(sf::Mouse&, sf::Keyboard&) override;
    virtual void load_textures() override;
    void new_round();
    void end_game();
    bool is_game_over();
    bool is_round_over();
    bool is_time_up();
    bool is_playing;

    std::list<Player*> players;
    std::list<Bomb*> bombs;
    std::list<Fire*> fires;
    std::list<Powerup*> powerups;
    std::list<Wooden_box*> wooden_boxes;
    std::list<Solid_box*> solid_boxes;

    int current_round;
    sf::Clock round_timer;

    sf::Texture fire_texture;
    sf::Texture player1_texture;
    sf::Texture player2_texture;
    sf::Texture player3_texture;
    sf::Texture player4_texture;
    sf::Texture solid_box_texture;
    sf::Texture wooden_box_texture;
    sf::Texture bomb_texture;
    sf::Texture push_texture;
    sf::Texture extra_bomb_texture;
    sf::Texture bigger_blast_texture;
    sf::Texture speed_texture;
};

class Menu_state: public State
{
public:
    Menu_state(): State("Menu_state")
    {}

    void update(sf::Mouse&, sf::Keyboard&) override;
    void draw(sf::RenderWindow&) override;

private:
    void user_input_handler(sf::Mouse&, sf::Keyboard&) override;
    void load_textures() override;
};
#endif
