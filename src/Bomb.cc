#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"
#include "Bomb.h"
#include "Fire.h"
#include <stdlib.h>
#include <sstream>

Bomb::Bomb(sf::Vector2f pos, sf::Texture& texture, Player* player, int fire_radius):
    Game_object(pos, texture),
    owner{player},
    fuse_timer{},
    speed{3},
    radius{fire_radius},
    is_gliding{false},
    move_direction{}
{}

Bomb::~Bomb()
{
    owner = nullptr;
    delete owner;
}

bool Bomb::is_blasted() const
{
    return fuse_timer.getElapsedTime().asSeconds() > 3;
}

void Bomb::update()
{
    if(is_gliding)
    {
        if (move_direction == "right")
        {
            move(speed,0);
        }
        else if (move_direction == "left")
        {
            move(-speed,0);
        }
        else if (move_direction == "up")
        {
            move(0,-speed);
        }
        else if (move_direction == "down")
        {
            move(0,speed);
        }
    }
    else
    {
        if ((int)old_position.x % 50 < 5 && (int)old_position.x % 50 != 0)
        {
            move(-1,0);
        }
        else if ((int)old_position.y % 50 < 5 && (int)old_position.y % 50 != 0)
        {
            move(0,-1);
        }
        else if ((int)old_position.y % 50 > 45 && (int)old_position.y % 50 != 0)
        {
            move(0,1);
        }
        else if ((int)old_position.x % 50 > 45 && (int)old_position.x % 50 != 0)
        {
            move(1,0);
        }
    }
}

// Bomb::apply_on_hit_effect stops gliding bomb upon collision
void Bomb::apply_on_hit_effect(Game_object* object)
{
    if (dynamic_cast<Player*>(object) != nullptr)
    {
        if (abs(old_position.x - object->get_old_position().x) <= 50 &&
        abs(old_position.y - object->get_old_position().y) <= 50)
        {
            return;
        }
    }
    is_gliding = false;
}

void Bomb::glide(std::string direction)
{
    move_direction = direction;
    is_gliding = true;
}

void Bomb::spawn_fire(std::list<Wooden_box*>& wooden_boxes,
    std::list<Solid_box*>& solid_boxes,
    std::list<Fire*>& fires,
    sf::Texture& fire_texture)
{
    undo_last_move();

    sf::Vector2f pos{get_position()};
    fires.push_back(new Fire {pos, fire_texture, owner});
    for (int i=1; i < radius && !solidbox_at_pos(solid_boxes, pos.x+50*i, pos.y);i++)
    {
        sf::Vector2f newPos{pos.x + 50*i, pos.y};
        fires.push_back(new Fire {newPos, fire_texture, owner});
        if (woodenbox_at_pos(wooden_boxes, pos.x+50*i, pos.y))
        {
            owner->increase_score(1);
            break;
        }
    }
    for (int i=1; i < radius && !solidbox_at_pos(solid_boxes, pos.x-50*i,pos.y);i++)
    {
        sf::Vector2f newPos{pos.x - 50*i, pos.y};
        fires.push_back(new Fire {newPos, fire_texture, owner});
        if (woodenbox_at_pos(wooden_boxes, pos.x-50*i, pos.y))
        {
            owner->increase_score(1);
            break;
        }
    }
    for (int i=1; i < radius && !solidbox_at_pos(solid_boxes, pos.x,pos.y+50*i);i++)
    {
        sf::Vector2f newPos{pos.x, pos.y + 50*i};
        fires.push_back(new Fire {newPos, fire_texture, owner}); fires.back()->set_rotation(90);
        if (woodenbox_at_pos(wooden_boxes, pos.x, pos.y+50*i))
        {
            owner->increase_score(1);
            break;
        }
    }
    for (int i=1; i < radius && !solidbox_at_pos(solid_boxes, pos.x,pos.y-50*i);i++)
    {
        sf::Vector2f newPos{pos.x, pos.y - 50*i};
        fires.push_back(new Fire {newPos, fire_texture, owner});
        fires.back()->set_rotation(90);
        if (woodenbox_at_pos(wooden_boxes, pos.x, pos.y-50*i))
        {
            owner->increase_score(1);
            break;
        }
    }
}

bool Bomb::solidbox_at_pos(std::list<Solid_box*> & lst, float x, float y) const
{
    for (Solid_box* obj :  lst)
    {
        if (obj->get_position().x == x && obj->get_position().y == y)
        {
            return true;
        }
    }
    return false;
}

bool Bomb::woodenbox_at_pos(std::list<Wooden_box*> & lst, float x, float y) const
{
    for (Wooden_box* obj :  lst)
    {
        if (obj->get_position().x == x && obj->get_position().y == y)
        {
            return true;
        }
    }
    return false;
}

void Bomb::draw(sf::RenderWindow& window, sf::Font& font)
{
    std::ostringstream info;
    info << (int)(4 - fuse_timer.getElapsedTime().asSeconds());
    sf::Text text0(info.str(), font, 15);
    text0.setPosition(position.x - 4, position.y - 4);
    text0.setFillColor(sf::Color::Red);
    window.draw(sprite);
    window.draw(text0);
}
