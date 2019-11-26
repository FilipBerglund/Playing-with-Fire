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

  
   // bool contains(sf::Mouse&);
 virtual bool click(sf::Mouse&)=0;

  sf::Sprite get_drawable() const
    {
      return sprite;
    }
  
 private:
  sf::Sprite sprite;


};

class Bool_button : public Menu_button
{
 Public:
  
    _button();
   Menu_button(sf::Vector2f pos, sf::Sprite s);
   
 private:
   sf::Sprite sprite;
  
}

class Int_button: public Menu_button
{
 public:
  Int_button();
  Int_button(sf::Vector2f pos, sf::Texture s0, sf::Texture s1, sf::Texture s2, sf::Texture s3, sf::Texture s4 , sf::Texture sbg);
  
  //bool contains(sf::Mouse&);
   bool click(sf::Mouse&) override;
   int get_value(){return value;}
   
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
