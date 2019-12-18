#include "catch.hpp"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <thread>
#include <chrono>

TEST_CASE("Fire")
{
    sf::Vector2f pos{50,100};
    sf::Texture texture{};
    texture.loadFromFile("textures/player1_texture.png");
    Player player1{pos, texture, false, 3, 1, 2, 3, "player 1"};
    Player player2{pos, texture, false, 3, 1, 2, 3, "player 1"};
    Player * player1ptr{&player1};
    Player * player2ptr{&player2};
    
    Fire fire{pos, texture, player1ptr};
    // Fire should be axtinguished after 3s
    CHECK_FALSE(fire.is_extinguished());
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    CHECK(fire.is_extinguished());

    CHECK(player2.is_immune()); // Player should be immune in the beginning.
    fire.apply_on_hit_effect(player2ptr); // Fire shoud not damage Player when immune
    CHECK(player2.get_health()==3); 
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    CHECK_FALSE(player2.is_immune()); // Player should not be immune after 5s
    fire.apply_on_hit_effect(player2ptr); // Fire should now damage player
    CHECK(player2.get_health()==2);
    CHECK(player2.is_immune()); // Fire should have made Plauyer immune
}
