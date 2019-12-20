#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>

#include <iostream> //For debugging
#include <string>

class Game_object
{
public:
    Game_object(sf::Vector2f pos, sf::Texture & texture):
    sprite{}, position{pos}, old_position{pos}
    {
        sprite.setTexture(texture);
        sprite.setOrigin(hitbox().width/2, hitbox().height/2);
        sprite.setPosition(pos);
    }

    virtual ~Game_object() = default;

    virtual void draw(sf::RenderWindow& window)
    {
        window.draw(sprite);
    }

    void set_position(sf::Vector2f pos)
    {
        old_position = position;
        position = pos;
        sprite.setPosition(pos);
    }

    void move(sf::Vector2f direction)
    {
        old_position = position;
        position += direction;
        sprite.setPosition(position);
    }

    void move(float dx, float dy)
    {
        old_position = position;
        position += sf::Vector2f(dx, dy);
        sprite.setPosition(position);
    }

    void move(int dx, int dy)
    {
        old_position = position;
        position += sf::Vector2f(dx, dy);
        sprite.setPosition(position);
    }

    void move(int dx, float dy)
    {
        old_position = position;
        position += sf::Vector2f(dx, dy);
        sprite.setPosition(position);
    }

    void move(float dx, int dy)
    {
        old_position = position;
        position += sf::Vector2f(dx, dy);
        sprite.setPosition(position);
    }

    sf::Vector2f get_position() const
    {
        return position;
    }

    sf::Vector2f get_old_position() const
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
        old_position = position;
        position = sf::Vector2f(roundedx, roundedy);
        sprite.setPosition(roundedx, roundedy);
    }

    sf::Rect<float> hitbox() const
    {
        return sprite.getGlobalBounds();
    }

protected:
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Vector2f old_position;
};
#endif
