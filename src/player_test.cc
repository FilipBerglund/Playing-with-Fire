#include "catch.hpp"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <thread>
#include <chrono>
#include <iostream>

TEST_CASE("Player")
{
    sf::Vector2f pos{50,100};
    sf::Texture texture{};
    texture.loadFromFile("textures/player1_texture.png");
    Player player1{pos, texture, false, 3, 1, 2, 3, "player 1"};

    // Player should take damage and should be dead after getting to 0 HP
    CHECK_FALSE(player1.is_dead());
    player1.reduce_health(3);
    CHECK(player1.get_health() == 0);
    CHECK(player1.is_dead());
    player1.new_round();
    CHECK(player1.get_health()==3);

    Player player2{pos, texture, false, 3, 1, 2, 3, "player 1"};
    Player * player1ptr{&player1};
    Player * player2ptr{&player2};

    //CHECK(player2.request_to_drop_bomb());
    
    // Collisions with bombs
    sf::Vector2f bomb_pos{0,100};
    Bomb bomb{bomb_pos, texture, player1ptr, 2};
    Bomb * bombptr{&bomb};

    CHECK_FALSE(player2.get_push_powerup());
    player2.apply_on_hit_effect(bombptr); // Shouldn't do anthing without powerup. 
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    CHECK(bomb.get_position()==bomb_pos);
    player2.set_push_powerup(true);
    CHECK(player2.get_push_powerup());
    player2.apply_on_hit_effect(bombptr); // Should cause bomb to move 
    bomb.update();
    //CHECK(bomb.get_position()!=bomb_pos);
    //CHECK(bomb.get_position().x!=bomb_pos.x);
    //CHECK(bomb.get_position().y!=bomb_pos.y);

    // Speed
    CHECK(player2.get_speed() == 1);
    player2.increase_speed(1);
    CHECK(player2.get_speed() == 2);

    CHECK(player2.get_fire_size() == 2);
    player2.increase_fire_size(1);
    CHECK(player2.get_fire_size() == 3);

    CHECK(player2.get_score() == 0);
    player2.increase_score(25);
    CHECK(player2.get_score() == 25);

    Bomb * bomb2ptr;
    bomb2ptr = player2.create_bomb(texture);
    CHECK(bomb2ptr->get_position() == pos);
    CHECK(bomb2ptr->get_owner() == player2ptr);

}
