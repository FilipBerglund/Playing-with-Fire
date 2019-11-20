#ifndef MENU_BUTTON
#define MENU_BUTTON

#include <string>
#include <list>
#include <SFML/Graphics.hpp>

class Menu_button
{
public:
   Menu_button();
   Menu_button(sf::Vector2f pos, sf::Sprite s);

  
  bool contains(sf::Mouse&);
  bool click(sf::Mouse&);

  sf::Sprite get_drawable() const
    {
      return sprite;
    }
  
 private:
  sf::Sprite sprite;
  sf::Texture; 

};

class bool_button : public Menu_button
{
 Public:
 
 private:
  
  
}

class Int_button : public Menu_button
{
 Public:
  Int_button();
  Int_button(sf::Vector2f pos, sf::Sprite s0, sf::Sprite s1, sf::Sprite s2, sf::Sprite s3, sf::Sprite s4 , sf::Sprite sbg);
  
   bool contains(sf::Mouse&);
   bool click(sf::Mouse&);
   int get_value(){return value;}
 private:
   int value{};
  sf::Sprite sprite_background;
  sf::Sprite sprite0;
  sf::Sprite sprite1;
  sf::Sprite sprite2;
  sf::Sprite sprite3;
  sf::Sprite sprite4;
  
}



#endif
