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
#include <random>


class Npc: public Player
{
public:
    Npc(sf::Vector2f, sf::Texture&, bool,
    int, int, int, int, std::string);

    ~Npc() = default;

    void update(std::list<Player*>&, std::list<Bomb*>&,
            std::list<Fire*>&, std::list<Powerup*>&,
            std::list<Wooden_box*>&, std::list<Solid_box*>&);

protected:
    virtual int local_score(std::string) const = 0;

    virtual void score_assigner(std::list<Bomb*>&,
            int&, int&, int&, int&, int&,
            sf::Vector2f, sf::Vector2f) const = 0;
    virtual void score_assigner(std::list<Fire*>&,
            int&, int&, int&, int&, int&,
            sf::Vector2f, sf::Vector2f) const = 0;
    virtual void score_assigner(std::list<Powerup*>&,
            int&, int&, int&, int&, int&,
            sf::Vector2f, sf::Vector2f) const = 0;
    void score_assigner(std::list<Wooden_box*>&,
            int&, int&, int&, int&,
            sf::Vector2f, sf::Vector2f);
    void score_assigner(std::list<Solid_box*>&,
            int&, int&, int&, int&,
            sf::Vector2f, sf::Vector2f) const;
    virtual void score_assigner(std::list<Player*>&,
            int&, int&, int&, int&, int&,
            sf::Vector2f, sf::Vector2f) = 0;
    void compute_scores(int&,int&,int&,int&,int&,
            std::list<Player*>&, std::list<Bomb*>&,
            std::list<Fire*>&, std::list<Powerup*>&,
            std::list<Wooden_box*>&, std::list<Solid_box*>&);
    void move(int,int,int,int,int);

    sf::Vector2f direction{0,0};

    std::random_device rd{};
    std::mt19937 mt{rd()};
    std::uniform_int_distribution<int> dist{0,99};
};

#endif
