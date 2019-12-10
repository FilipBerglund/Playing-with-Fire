#ifndef BOMB_H
#define BOMB_H

#include <SFML/Graphics.hpp>
#include "Game_object.h"
#include <string>
#include <list>
#include "Fire.h"
#include "Box.h"

class Player;
class Bomb: public Game_object
{
public:
    Bomb(sf::Vector2f, sf::Texture, Player*);
    void apply_on_hit_effect(Game_object*) {}
    void glide(std::string) {};
    bool is_gliding() {return false;}
    void spawn_fire(std::list<Wooden_box*> wooden_boxes, 
		    std::list<Solid_box*> solid_boxes,
		    std::list<Fire*> fires,
            sf::Texture fire_texture);
private:
    Player* owner;
    bool solidbox_at_pos(float x, float y);
    bool woodenbox_at_pos(float x, float y);
    int radius;
};
#endif
