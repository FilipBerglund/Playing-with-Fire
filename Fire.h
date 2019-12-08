#ifndef FIRE_H
#define FIRE_H

#include <SFML/Graphics.hpp>
#include "Box.h"
#include "Player.h"
#include "Game_object.h"

class Fire: public Game_object
{
public:
  
    Fire(sf::Vector2f, sf::Texture&, Player*);
    
    void apply_on_hit_effect(Game_object* object) override;

    bool is_extinguished() const;
    
private:
    sf::Clock aflame_timer;
};
#endif        
