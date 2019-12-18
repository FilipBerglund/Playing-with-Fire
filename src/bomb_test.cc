#include "catch.hpp"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bomb.h"
#include "Box.h"
#include <thread>
#include <chrono>

TEST_CASE("Bomb")
{
    sf::Vector2f pos{50,100};
    sf::Texture texture{};
    texture.loadFromFile("textures/bomb_texture.png");
    Player player{pos, texture, false, 3, 1, 2, 3, "player 1"};
    Player * playerptr{&player};
    Bomb bomb{pos, texture, playerptr, 3};
    
    CHECK(bomb.get_owner() == playerptr);
    CHECK(bomb.get_position() == pos);

    // Should glide by 3 pixels on update
    // Note: positive direction is down
    bomb.glide("right");
    bomb.update();
    sf::Vector2f new_pos_right = sf::Vector2f{53,100};
    CHECK(bomb.get_position() == new_pos_right);

    bomb.glide("down");
    bomb.update();
    sf::Vector2f new_pos_down = sf::Vector2f{53,103};
    CHECK(bomb.get_position() == new_pos_down);

    bomb.glide("left");
    bomb.update();
    sf::Vector2f new_pos_left = sf::Vector2f{50,103};
    CHECK(bomb.get_position() == new_pos_left);

    bomb.glide("up");
    bomb.update();
    sf::Vector2f new_pos_up = sf::Vector2f{50,100};
    CHECK(bomb.get_position() == new_pos_up);

    // is_blasted should be set after 3s
    CHECK_FALSE(bomb.is_blasted());
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    CHECK(bomb.is_blasted());


    // Checking that apply_on_hit_effect stops gliding bomb
    sf::Vector2f box_pos{50,0};
    Wooden_box box{box_pos, texture};
    Box * boxptr(&box);

    bomb.glide("up");
    bomb.update();
    sf::Vector2f new_pos{50,97};
    CHECK(bomb.get_position() == new_pos);
    bomb.apply_on_hit_effect(boxptr);
    bomb.update(); // apply_on_hit_effect should have stoped bomb from gliding 
    sf::Vector2f reset_pos{50,98};
    CHECK(bomb.get_position() == reset_pos);
    
    // Testing spawn_fire
    sf::Vector2f wooden_box_pos{50,50};
    Wooden_box wooden_box{wooden_box_pos, texture};
    Wooden_box * wooden_box_ptr(&wooden_box);
    
    sf::Vector2f solid_box_pos{0,100};
    Solid_box solid_box{solid_box_pos, texture};
    Solid_box * solid_box_ptr(&solid_box);

    std::list<Wooden_box*> wooden_boxes;
    std::list<Solid_box*> solid_boxes;
    std::list<Fire*> fires;

    wooden_boxes.push_back(wooden_box_ptr);
    solid_boxes.push_back(solid_box_ptr);

    bomb.spawn_fire(wooden_boxes, solid_boxes, fires, texture);
    CHECK(fires.size() == 6);
    // We have radius 3, solid box blocking at (0,100) and a wooden box 
    // blocking at (50,50), so fires should spawn at (50,100),(100,100),
    // (150,100),(50,150),(50,200), and (50,50), in that order.
    sf::Vector2f pos1{50,100};
    sf::Vector2f pos2{100,100};
    sf::Vector2f pos3{150,100};
    sf::Vector2f pos4{50,150};
    sf::Vector2f pos5{50,200};
    sf::Vector2f pos6{50,50};
    CHECK(fires.front()->get_position() == pos1);
    fires.pop_front();
    CHECK(fires.front()->get_position() == pos2);
    fires.pop_front();
    CHECK(fires.front()->get_position() == pos3);
    fires.pop_front();
    CHECK(fires.front()->get_position() == pos4);
    fires.pop_front();
    CHECK(fires.front()->get_position() == pos5);
    fires.pop_front();
    CHECK(fires.front()->get_position() == pos6);

}
