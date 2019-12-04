#ifndef NPC_H
#define NPC_h
#include <Player.h>
#include <SFML/Graphics.hpp>
#include <string>

class NPC: public Player
{
public:
    NPC(sf::Vector2f, sf::Texture &, int, bool,
	int, int, int, int, std::string);

    ~NPC() = default;

    void update();
    
private:
    int local_score() const;
};

#endif
