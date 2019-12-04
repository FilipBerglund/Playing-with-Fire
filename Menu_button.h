#ifndef MENU_BUTTON
#define MENU_BUTTON

#include <string>
#include <list>
#include <SFML/Graphics.hpp>

class Menu_button
{
public:
//   Menu_button();

  
   // bool contains(sf::Mouse&);
 virtual bool click(sf::Mouse&)=0;
 virtual void draw(sf::RenderWindow&)=0; 
 private:

};

class Start_button : public Menu_button
{
 public:
  
 //  Start_button();
   Start_button(sf::Vector2f pos, sf::Texture s);
   
   bool click(sf::Mouse&) override;   
   void draw(sf::RenderWindow&) override;
 
 private:
   sf::Sprite sprite;
  
};

class Int_button: public Menu_button
{
 public:
  //Int_button();
  Int_button(sf::Vector2f pos, sf::Texture s0, sf::Texture s1,
	     sf::Texture   s2, sf::Texture s3, sf::Texture s4,
	     sf::Texture  sbg);
  
  //bool contains(sf::Mouse&);
   bool click(sf::Mouse&) override;
   int get_value(){return value;}
   void draw(sf::RenderWindow&) override;
   
 private:
 
  int value{};
  sf::Sprite sprite_background;
  sf::Sprite sprite0;
  sf::Sprite sprite1;
  sf::Sprite sprite2;
  sf::Sprite sprite3;
  sf::Sprite sprite4; 
};



#endif
