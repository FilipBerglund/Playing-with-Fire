#include "catch.hpp"
#include <SFML/Graphics.hpp>
#include "Player.h"

TEST_CASE()
{
    sf::Vector2f pos{50,100};
    sf::Texture texture{};
    texture.loadFromFile("textures/player1_texture.png");
    Player player1{pos, texture, false, 3, 1, 2, 3, "player 1"};
    Player player2{pos, texture, false, 3, 1, 2, 3, "player 1"};
    Player * player1ptr{&player1};
    Player * player2ptr{&player2};
    
    Fire fire{pos, texture, player1ptr};
    player2.reduce_health(1);
    CHECK_FALSE(player2.is_immune());
    fire.apply_on_hit_effect(player2ptr); //Player health should reduce
    CHECK(player2.get_health()==1); 
    player2.make_immune();
    fire.apply_on_hit_effect(player2ptr);
    CHECK(player2.get_health()==1); // Player should be immune
    

    CHECK(player2.request_to_drop_bomb());

}
