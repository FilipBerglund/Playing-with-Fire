#ifndef NPC_H
#define NPC_H
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include "Bomb.h"
#include "Fire.h"
#include "Powerup.h"
#include "Box.h"


class Npc: public Player
{
public:
    Npc(sf::Vector2f, sf::Texture &, int, bool,
	int, int, int, int, std::string);

    ~Npc() = default;

    void update(std::list<Player*>&, std::list<Bomb*>&, std::list<Fire*>&,
	        std::list<Powerup*>&, std::list<Wooden_box*>&, std::list<Solid_box*>&);
    
protected:
    int local_score(std::string) const;
    void score_assigner(std::list<Bomb*>& ,int&, int&, int&, int&, int&,
			sf::Vector2f, sf::Vector2f, std::string) const;
    void score_assigner(std::list<Fire*>& ,int&, int&, int&, int&, int&,
			sf::Vector2f, sf::Vector2f, std::string) const;
    void score_assigner(std::list<Powerup*>& ,int&, int&, int&, int&, int&,
			sf::Vector2f, sf::Vector2f, std::string) const;
    void score_assigner(std::list<Wooden_box*>& ,int&, int&, int&, int&, int&,
			sf::Vector2f, sf::Vector2f, std::string) const;
    void score_assigner(std::list<Solid_box*>& ,int&, int&, int&, int&, int&,
			sf::Vector2f, sf::Vector2f, std::string) const;
    void score_assigner(std::list<Player*>& ,int&, int&, int&, int&, int&,
			sf::Vector2f, sf::Vector2f);
};

#endif
