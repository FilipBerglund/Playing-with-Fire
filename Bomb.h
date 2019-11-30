#ifndef BOMB_H
#define BOMB_H

#include <SFML/Graphics.hpp>
#include "Box.h"
#include "Fire.h"
#include "Player.h"
#include "Game_state.h"


class Bomb: public Game_object
{
 public:
    Bomb (sf::Vector2f pos, sf::Texture texture,
     Player* player);
    //TODO: Lägg till en funktion som kollar om Bomben ska explodera.
    //Den funktionen körs i game_state. Sedan om den returnerar true
    //kommer game_state kalla på spawn_fire.
    void spawn_fire(Player* owner, float timer, Fire fire);
    void update() override;

    //void collision (Game_object*);
    void apply_on_hit_effect(Game_object*);

    void glide(std::string direction);
    //TODO: Dessa två behövs inte.
    bool is_gliding() const;
    void set_is_gliding(bool sam);

 private:
    Player* owner;
    
    //TODO: Denna behövs inte.
    float timer;

    //TODO: Kanske ett bättre variabelnamn, förslagsvis detonation_timer
    //eller fuse_timer.
    sf::Clock ticking_bomb; 

};
#endif
