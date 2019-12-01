#ifndef FIRE_H
#define FIRE_H

#include <SFML/Graphics.hpp>
#include "Box.h"
#include "Game_state.h"
#include "Player.h"


class Fire: public Game_object
{
 public:
<<<<<<< HEAD
    Fire (sf::Vector2f, sf::Texture, Player*);
    bool is_dead() const;
    void give_points(Player* owner);
=======
     //TODO: fire_size och timer behövs inte.
    Fire (sf::Vector2f pos, sf::Sprite sprite, int timer, int fire_size, Player*);

    //TODO: Dessa två funktioner behövs inte.
    bool is_boosted();
    void fire_boost(int fire_size);


    //TODO: Lägg till funktionen apply_on_hit_effect.
    //TODO: Denna funktion behövs inte.
    void give_points( Player owner);
>>>>>>> 93411fa2be2e3b8d5e9a5a3861169f1b421033ab
    void update() override;

    //TODO: lägg till en boolsk funktion som kollar om Fire
    //ska tas bort från spelet.

 private:
<<<<<<< HEAD
    Player* owner;
    int timer;
    int fire_size;
=======
    // TODO: Dessa tre är inte funktioner så skriv inte ().
    // fire_size behövs inte.
    Player owner();
    int timer();
    int fire_size();
>>>>>>> 93411fa2be2e3b8d5e9a5a3861169f1b421033ab

    // TODO: Ha gärna ett tydilgare variabelnamn på denna.
    sf::Clock fire_rate;

};
#endif        
