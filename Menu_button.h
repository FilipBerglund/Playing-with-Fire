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
  virtual bool click(sf::Mouse&, sf::RenderWindow&)=0;
 virtual void draw(sf::RenderWindow&)=0; 
 private:

};

class Start_button : public Menu_button
{
 public:
  
 //  Start_button();
  Start_button(sf::Vector2f, sf::Texture&);
   
  bool click(sf::Mouse&, sf::RenderWindow&) override;   
   void draw(sf::RenderWindow&) override;
   void new_pos(sf::Vector2f);
   void new_sprite(sf::Texture&);
 
 private:
   sf::Sprite sprite;
  
};

class Int_button: public Menu_button
{
 public:
  //Int_button();
  Int_button(sf::Vector2f, sf::Texture&, sf::Texture&);
  
  //bool contains(sf::Mouse&);
  bool click(sf::Mouse&, sf::RenderWindow&) override;
   int get_value() {return value;}
   void draw(sf::RenderWindow&) override;
   
 private:
 
  int value;
  sf::Sprite menu_bar;
  sf::RectangleShape button_0;
  sf::RectangleShape button_1;
  sf::RectangleShape button_2;
  sf::RectangleShape button_3;
  sf::RectangleShape button_4;
};

#endif
