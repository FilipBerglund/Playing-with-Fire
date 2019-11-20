#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <SFML/Graphics.hpp>

class Game_object
{
public:
    Game_object(sf::Vector2f pos, sf::Texture texture):
    sprite{texture}
    {
        sprite.setPosition(pos);
    }

    sf::Sprite get_drawable() const
    {
        return sprite;
    }

    void update() {};
    bool collision(Game_object) {};
    sf::IntRect& hit_box() const
    {
        return sprite.getTextureRect();
    }

private:
    sf::Sprite sprite;
};
#endif
