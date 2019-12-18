#include "catch.hpp"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Powerup.h"
#include <thread>
#include <chrono>

TEST_CASE("Powerup")
{
    sf::Vector2f pos{50,100};
    sf::Texture texture{};
    texture.loadFromFile("textures/player1_texture.png");
    Player player{pos, texture, false, 3, 1, 2, 3, "player 1"};
    Player * playerptr{&player};
    
    Speed speed{pos,texture};
    Bigger_blast bigger_blast{pos,texture};
    Extra_bomb extra_bomb{pos,texture};
    Push push{pos,texture};

    CHECK(player.get_speed()==1);
    CHECK(player.get_fire_size()==2);
    CHECK(player.get_push_powerup()==false);

    speed.apply_on_hit_effect(playerptr);
    biger_blast.apply_on_hit_effect(playerptr);
    extra_bomb.apply_on_hit_effect(playerptr);
    push.apply_on_hit_effect(playerptr);

    CHECK(player.get_speed()==2);
    CHECK(player.get_fire_size()==3);
    CHECK(player.get_push_powerup()==true);
}
