#ifndef BOMB_H
#define BOMB_H

#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include "Game_object.h"
#include "Box.h"
#include "Player.h"
#include "Fire.h"

class Player;
class Bomb: public Game_object
{
public:
    Bomb(sf::Vector2f, sf::Texture &, Player*, int);
    Bomb(const Bomb&) = delete;
    Bomb operator=(const Bomb&)= delete;

    ~Bomb();

    bool is_blasted() const;
    void update();
    void apply_on_hit_effect(Game_object*);
    void glide(std::string);

    void spawn_fire(std::list<Wooden_box*>& wooden_boxes,
                    std::list<Solid_box*>& solid_boxes,
                    std::list<Fire*> & fires,
                    sf::Texture& fire_texture);
    void draw(sf::RenderWindow&, sf::Font&);

private:
    Player* owner;
    sf::Clock fuse_timer;
    float speed;
    int radius;
    bool is_gliding;
    std::string move_direction;

    bool solidbox_at_pos(std::list<Solid_box*> & lst, float x, float y) const;
    bool woodenbox_at_pos(std::list<Wooden_box*> & lst, float x, float y) const;
};
#endif
