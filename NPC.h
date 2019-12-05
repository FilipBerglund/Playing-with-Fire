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

    void update(list<Game_object*>&, list<Game_object*>&, list<Game_object*>&,
	        list<Game_object*>&, list<Game_object*>&, list<Game_object*>&);
    
private:
    int local_score(std::string) const;
    void score_assigner(list<Game_object*>& ,int&, int&, int&, int&, int&,
			sf::Vector2f, sf::Vector2f, std::string) const;
    void score_assigner(list<Player*>& ,int&, int&, int&, int&, int&,
			sf::Vector2f, sf::Vector2f) const;
};

#endif
