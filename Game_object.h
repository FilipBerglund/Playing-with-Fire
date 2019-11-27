#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <SFML/Graphics.hpp>

#include <iostream> //For debugging
#include <string>

class Game_object
{
public:
    Game_object(sf::Vector2f pos, sf::Texture & texture):
    sprite{}, old_position{pos}
    {
        sprite.setPosition(pos);
        sprite.setTexture(texture);
        std::cout << "Constructing Game_object" << std::endl;
        std::cout << "Texture ptr is: " << sprite.getTexture() << std::endl;
        std::cout << "Size is: " << sprite.getTexture()->getSize().x 
                  << " by " << sprite.getTexture()->getSize().y << std::endl;
    }

    sf::Sprite get_drawable() const
    {
        std::cout << "Getting drawable, texture is: " << sprite.getTexture() << std::endl;
        std::cout << "Size is: " << sprite.getTexture()->getSize().x 
                  << " by " << sprite.getTexture()->getSize().y << std::endl;
        return sprite;
    }

    sf::Vector2f get_position()
    {
        return sprite.getPosition();
    }

    virtual void update(sf::Keyboard) {};
    virtual void apply_on_hit_effect(Game_object*) {};
    void undo_last_move()
    {
        sprite.setPosition(old_position);
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
