include "Player.h"


Player::Player(sf::Vector2f pos, sf::Sprite sprite, int cooldown, int in_push,
               int in_health, int in_speed, int in_fire, int in_cd):
       Game_object(pos, sprite), push_powerup{in_push}, health{in_health}, speed{in_speed}, fire_size{in_fire},
       score{0}, cd{in_cd}, immune_clock{}, bomb_cds{}, spawn_point{pos},
       initial_push_powerup{in_push}, initial_health{in_health}, initial_speed{in_speed},
       initial_fire_size{in_fire}, initial_cd{in_cd}
{
    sf::Clock new_clock;
    bomb_cds.push_back(new_clock);  //Listan får storlek 1.
    sprite.setOrigin(hitbox().width/2, hitbox().height/2); //Origin blir i mitten.
}


void Player::new_round()  //Variabler återställs vid ny runda.
{
    push_powerup = initial_push_powerup;
    health = initial_health;
    speed = initial_speed;
    fire_size = initial_fire_size;
    cd = initial_cd;
    sprite.setPosition(spawn_point); 
    bomb_cds.resize(1);
    bomb_cds[0].restart(); 
}


/*Spelarens applyfunktion ansvarar för vad som händer vid
  kollision med ett annat object om det är av typen Game_object.
  Game_state tar själv bort powerups vid kollision med spelare
  så spelare behöver endast hantera kollision med bomber.*/ 
void Player::apply_on_hit_effect(Game_object* object) const 
{
    /*object kommer alltid vara en bombpekare men eftersom apply
      är överlagrad från Game_object så måste vi använda
      dyanmic_cast för att behandla object som en bombpekare.
      Därmed behöver vi inte kolla om pekaren ptr nedanför
      är lika med nullptr.*/ 
    Bomb* ptr = dynamic_cast<Bomb*>(object);
	
    if (push_powerup == true)  
    { 	    
	/*I de stora if-satsern nedanför kollar vi först  kollision i ett visst led
	  och sedan kollar vi spelarens and bombens ursprungliga positioner
	  för att bestämma i vilken riktning bomben ska skjutas iväg.*/ 
	if (sprite.getPosition().x + hitbox().width/2 >=                
	    ptr->sprite.getPosition().x - ptr->hitbox().width/2 &&   
	    old_position.x + hitbox().width/2 <
	    ptr->old_position.x - hitbox().width/2)
	{
	    ptr->glide("right");
	}
	else if(sprite.getPosition().x - hitbox().width/2 <=
		ptr->sprite.getPosition().x + ptr->hitbox().width/2 &&
		old_position.x + hitbox().width/2 >
		ptr->old_position.x - ptr->hitbox().width/2)
	{
	    ptr->glide("left");
	}
	else if(sprite.getPosition().y - hitbox().height/2 <=
		ptr->sprite.getPosition().y + ptr->hitbox().height/2 &&
		old_position.y + hitbox().height/2 >
		ptr->old_position.y - ptr->hitbox().width/2)
	{
	    ptr->glide("up");
	}
	else  // If-sats ej nödvändig p.g.a. uteslutning. 
	{
	    ptr->glide("down");
	}	   
    }
    else if (ptr->is_gliding() == true)  //push_powerup == false så bomben ska stanna.
    {
	ptr->sprite.setPosition(ptr->old_position);
	ptr->set_is_gliding(false);
    }
}


void Player::set_push_powerup(bool var) 
{
    push_powerup = var;
}


bool Player::get_push_powerup() const
{
    return push_powerup;
}


void Player::reduce_health(int damage) 
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


int Player::get_health() const
{
    return health;
}


bool Player::is_dead() const //Kollar om spelaren är död.
{
    return health == 0;
}


void Player::increase_speed(int var)
{
    speed += var;
}

int Player::get_speed() const
{
    return speed;
}


void Player::increase_fire_size(int var)
{
    fire_size += var;
}

int Player::get_fire_size() const
{
    return fire_size;
}


void Player::increase_score(int add_score)
{
    score += add_score;
}


int Player::get_score() const
{
    return score;
}


void Player::give_bomb()
{
    sf::Clock new_clock;
    bomb_cds.push_back(new_clock); 
}


bool Player::is_immune() const
{
    return immune_clock.getElapsedTime().asSeconds() <= 5;
}


void Player::make_immune()
{
    immune_clock.restart();
}


Bomb* Player::drop_bomb()  //Hjälpfunktion när bomber ska droppas. 
{
    for (int i = 0; i < bomb_cds.size(), i++)  //Går igenom hela listan av klockor. 
    {
	if (bomb_cds[i].getElapsedTime().asSeconds() >= cd) //När detta uppfylls har spelaren möjligheten att droppa en bomb. 
	{
	    bomb_cds[i].restart();  
	    Bomb* ptr = new Bomb(this);
	    return ptr;
	}
    }
    return nullptr;  // Player kan inte droppa en bomb.
}

