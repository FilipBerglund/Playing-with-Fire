#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>

#include <iostream> //For debugging
#include <string>

class Game_object
{
public:
    Game_object(sf::Vector2f pos, sf::Texture & texture):
    sprite{}, old_position{pos}
    {
        sprite.setTexture(texture);
        sprite.setOrigin(hitbox().width/2, hitbox().height/2);
        sprite.setPosition(pos);
    }

    virtual ~Game_object() = default;

    sf::Sprite get_drawable() const
    {
        return sprite;
    }

    sf::Vector2f get_position()
    {
        return sprite.getPosition();
    }

    sf::Vector2f get_old_position()
    {
        return old_position;
    }

    void set_rotation(float angle)
    {
        return sprite.setRotation(angle);
    }

    virtual void apply_on_hit_effect(Game_object*) {};

    void undo_last_move()
    {
        int roundedx = (((int)get_position().x + 25) / 50 ) * 50;
        int roundedy = (((int)get_position().y + 25) / 50 ) * 50;
        sprite.setPosition(roundedx, roundedy);
    }

    sf::Rect<float> hitbox() const
    {
        return sprite.getGlobalBounds();
    }

protected:
    sf::Sprite sprite;
    sf::Vector2f old_position;
};
#endif
