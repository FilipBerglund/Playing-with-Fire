#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include "Menu_button.h"
#include <iostream>

//Menu_button::Menu_button()
//{
//}

//Start_button::Start_button()
//{
//}


Start_button::Start_button(sf::Vector2f pos, sf::Texture& texture):
  sprite{}
{
  sprite.setTexture(texture);
  sprite.setPosition(pos);
}

//Kollar om musen är på bool button
bool Start_button::click(sf::Mouse& mouse, sf::RenderWindow& window)
{

  if (sprite.getGlobalBounds().contains(mouse.getPosition(window).x , mouse.getPosition(window).y))
    {
      return true;
    }
  else
    {
      return false;
    }
}
//ritar Start button
void Start_button::draw(sf::RenderWindow& window)
{
  window.draw(sprite);

}

void Start_button::new_pos(sf::Vector2f newpos)
{
  sprite.setPosition(newpos);

}

void Start_button::new_sprite(sf::Texture& s)
{
  sprite.setTexture(s);
}

/*
 * Int_button
 *
 */

Int_button::Int_button(sf::Vector2f pos, sf::Texture& bar)
  :value{0}, menu_bar{bar}, button_0{}, button_1{},
   button_2{}, button_3{}, button_4{}
 {
  //menu's position
   menu_bar.setPosition(pos);

  //buttons' positions
   button_0.setSize(bsize);
   button_0.setPosition(pos.x + 64, pos.y + 13);
   button_0.setFillColor(sf::Color(255, 234, 0, 80));

   button_1.setSize(bsize);
   button_1.setPosition(pos.x + 121, pos.y + 13);
   button_1.setFillColor(sf::Color(255, 213, 0, 80));

   button_2.setSize(bsize);
   button_2.setPosition(pos.x + 177, pos.y + 13);
   button_2.setFillColor(sf::Color(255, 191, 2, 80));

   button_3.setSize(bsize);
   button_3.setPosition(pos.x + 233, pos.y + 13);
   button_3.setFillColor(sf::Color(255, 183, 0, 80));

   button_4.setSize(bsize);
   button_4.setPosition(pos.x + 289, pos.y + 13);
   button_4.setFillColor(sf::Color(255, 154, 0, 80));
 }
// Kollar vilken låda musen är över och anger rätt value

bool Int_button::click(sf::Mouse& mouse, sf::RenderWindow& window)
{
  if (button_0.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y))
    {
      value = 0;
      return true;
    }
  else if(button_1.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y))
    {
      value = 1;
      return true;
    }
  else if(button_2.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y))
    {
      value = 2;
      return true;
    }
  else if(button_3.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y))
    {
      value = 3;
      return true;
    }
  else if(button_4.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y))
    {
      value = 4;
      return true;
      }
  else
    {
      return false;
    }
}

void Int_button::draw(sf::RenderWindow& window)
{
  window.draw(menu_bar);
  switch(value)
    {
      case 0 :
      window.draw(button_0);
      break;
      case 1 :
      window.draw(button_1);
            break;
      case 2 :
      window.draw(button_2);
            break;
      case 3 :
      window.draw(button_3);
            break;
      case 4 :
      window.draw(button_4);
            break;
    }
}
