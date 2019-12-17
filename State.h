#ifndef STATE
#define STATE

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Powerup.h"
#include "Box.h"
#include "Bomb.h"
#include "Fire.h"

#include "Menu_button.h"
#include <random>

#include <string>
#include <list>

class Game_state;
class Menu_state;
class End_screen;
class State
{
public:
    State(std::string n): name{n}
    {}
    virtual ~State() = default;

    virtual void update(sf::Mouse&, sf::Keyboard&,
			Game_state*, Menu_state*,
			End_screen*, State**, sf::RenderWindow&) = 0;
    virtual void draw(sf::RenderWindow&) = 0;
    std::string name;
private:
    virtual void user_input_handler(sf::Mouse&, sf::Keyboard&,
				    Game_state*, Menu_state*,
				    End_screen*, State**, sf::RenderWindow&) = 0;
//    virtual void load_textures() = 0;
};

class Game_state: public State
{
public:
    Game_state();
    ~Game_state();

    void update(sf::Mouse&, sf::Keyboard&,
		Game_state*, Menu_state*,
		End_screen*, State**, sf::RenderWindow&) override;
    void draw(sf::RenderWindow&) override;
    void new_game(int, int, int, int);

private:
    void check_collisions();
    void user_input_handler(sf::Mouse&, sf::Keyboard&,
			    Game_state*, Menu_state*,
			    End_screen*, State**, sf::RenderWindow&) override;
 //   virtual void load_textures() override;
    void new_round();
    void initialize_map();
    void end_game(State**, End_screen*);
    int round_length;
    int number_of_rounds;
    bool is_game_over() const; 
    bool is_round_over() const; 
    bool is_time_up() const;
    bool is_playing;
    Start_button* quit_button;
    Start_button* back_button;

    sf::Texture& get_texture(sf::Texture&,sf::Texture&,sf::Texture&,sf::Texture&,int);
    std::random_device rd{};
    std::mt19937 mt{rd()};
    std::uniform_int_distribution<int> dist{0,99};


    std::list<Player*> players;
    std::list<Player*> alive_players;
    std::list<Bomb*> bombs;
    std::list<Fire*> fires;
    std::list<Powerup*> powerups;
    std::list<Wooden_box*> wooden_boxes;
    std::list<Solid_box*> solid_boxes;

    int current_round;
    sf::Clock round_timer;

    sf::Vector2f offset; 
    sf::Texture player1_texture;
    sf::Texture player2_texture;
    sf::Texture player3_texture;
    sf::Texture player4_texture;
    sf::Texture fire_texture;
    sf::Texture solid_box_texture;
    sf::Texture wooden_box_texture;
    sf::Texture bomb_texture;
    sf::Texture push_texture;
    sf::Texture extra_bomb_texture;
    sf::Texture bigger_blast_texture;
    sf::Texture speed_texture;
    sf::Texture quit_button_texture;
    sf::Texture back_button_texture;

    //Player data.
    void load_player_data();
    void load_game_data();
    void load_textures();
    std::vector<sf::Vector2f> player_positions;
    std::vector<std::string> player_names;
    /*
    std::vector<sf::Keyboard::Key> player1_buttons;
    std::vector<sf::Keyboard::Key> player2_buttons;
    std::vector<sf::Keyboard::Key> player3_buttons;
    std::vector<sf::Keyboard::Key> player4_buttons;
    */
    std::vector<std::vector<sf::Keyboard::Key>> player_buttons;
    std::vector<sf::Texture> player_textures;
};

class Menu_state: public State
{
public:
    Menu_state();
    ~Menu_state() = default;

void update(sf::Mouse&, sf::Keyboard&,
      Game_state*, Menu_state*,
      End_screen*, State**, sf::RenderWindow&) override;
void draw(sf::RenderWindow&) override;

private:
    void user_input_handler(sf::Mouse&, sf::Keyboard&,
    Game_state*, Menu_state*,
    End_screen*, State**, sf::RenderWindow&) override;
  //  void load_textures() override;

    sf::Texture start_texture;
    Start_button* start_button;
    sf::Sprite background;
    sf::Texture bg_texture;
    sf::Texture pc_menu;
    sf::Texture npc1_menu;
    sf::Texture npc2_menu;
    sf::Texture npc3_menu;
    Int_button* PC_button;
    Int_button* NPC1_button;
    Int_button* NPC2_button;
    Int_button* NPC3_button;
};

class End_screen: public State
{
 public:

  End_screen();
  ~End_screen();
  void new_players(std::list<Player*>);
  void draw(sf::RenderWindow&) override;
  void update(sf::Mouse& , sf::Keyboard&,
	      Game_state*, Menu_state*,
	      End_screen*, State**, sf::RenderWindow&) override;
 private:
  sf::Vector2f pos{50,50};
  sf::Texture button_texture;
  std::list<Player*> list_of_Player;
  Start_button* end_button;
  void user_input_handler(sf::Mouse& , sf::Keyboard&,
			  Game_state*, Menu_state*,
			  End_screen*, State**, sf::RenderWindow&) override;
};


#endif
