#include "Box.h"

void Box::apply_on_hit_effect(Game_object* object)
{
    object->undo_last_move();
}

bool Wooden_box::is_dead() const
{
    return health == 0;
}

void Wooden_box::reduce_health(int damage)
{
    if (health - damage <= 0)
    {
        health = 0;
    }
    else
    {
        health -= damage;
    }
}
