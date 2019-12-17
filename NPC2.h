#ifndef NPC2_H
#define NPC2_H
#include "NPC.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include "Bomb.h"
#include "Fire.h"
#include "Powerup.h"
#include "Box.h"


class Npc2: public Npc
{
public:
    Npc2(sf::Vector2f, sf::Texture&, std::string);

    ~Npc2() = default;
    
protected:
    int local_score(std::string) const override;
    void score_assigner(std::list<Bomb*>& ,int&, int&, int&, int&, int&,
			sf::Vector2f, sf::Vector2f) const override;
    void score_assigner(std::list<Fire*>& ,int&, int&, int&, int&, int&,
			sf::Vector2f, sf::Vector2f) const override;
    void score_assigner(std::list<Powerup*>& ,int&, int&, int&, int&, int&,
			sf::Vector2f, sf::Vector2f) const override;
    void score_assigner(std::list<Player*>& ,int&, int&, int&, int&, int&,
			sf::Vector2f, sf::Vector2f) override;
};

#endif
