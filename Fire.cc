#include <SFML/Graphics.hpp>
#include "Bomb.h"
#include "Player.h"
#include "Game_state"

#include "Fire.h"


int fire_size=5;

Fire::Fire(sf::Vector2f pos, sf::Sprite sprite, int timer, int fire_size, Player* player ) 
: Game_objects(pos, sprite), owner{player}
{
}


bool Fire::is_boosted()
{
    if (/*player boosted is applied*/)
    {
        return fire_boost;
    }
    else
    {
        /* code */
    }
    

}

void Fire::fire_boost(int fire_size)
{
    return fire_size + 2;
}

void Fire::give_points(Player owner)
{
    if (/*fire pointer to owner*/)
    {
        return /*Player.point*/ + 1;
    }
    else
    {
        /* code */
    }
    
    
}

void update() override
{

}