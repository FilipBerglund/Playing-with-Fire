#ifndef BOMB_H
#define BOMB_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Box.h"
//#include "Fire.h"
#include "Player.h"


class Bomb: public Game_object
{
 public:
    Bomb (sf::Vector2f pos, sf::Texture & texture,
     Player* player);
<<<<<<< HEAD
    //void set_owner(Player* owner, Fire fire);
    
    bool is_blasted() const;
    
=======
    //TODO: Lägg till en funktion som kollar om Bomben ska explodera.
    //Den funktionen körs i game_state. Sedan om den returnerar true
    //kommer game_state kalla på spawn_fire.
    void spawn_fire(Player* owner, float timer, Fire fire);
>>>>>>> 93411fa2be2e3b8d5e9a5a3861169f1b421033ab
    void update() override;
    
    void apply_on_hit_effect(Game_object*);
<<<<<<< HEAD
    
    void glide();
    
 private:
    
    bool is_gliding;
    / Player* owner;
    float speed;
    std::string direction;
    sf::Clock fuse_timer;
=======

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

>>>>>>> 93411fa2be2e3b8d5e9a5a3861169f1b421033ab
};
#endif
