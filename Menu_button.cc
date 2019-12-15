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
  // std::cout << "mouse pos: " << mouse.getPosition(window).x << " " << mouse.getPosition(window).y << std::endl;
  // std::cout << "sprite pos" << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
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
  // std::cout << "inside Start_button draw" << sprite.getPosition().x << "  "<<
  //  sprite.getPosition().y << std::endl;
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
  :menu_bar{bar}, value{0}
 {
  //menu's position
   menu_bar.setPosition(pos);
   
  //buttons' positions
   //float pc_selection = pos.y + 14;
   //float npc_selection = pos.y + 88;
   
   button_0.setSize(sf::Vector2f(50,50));
   button_0.setPosition(pos.x + 65, pos.y + 14);
   
   button_1.setSize(sf::Vector2f(50,50));
   button_1.setPosition(pos.x + 122, pos.y + 14);
   
   button_2.setSize(sf::Vector2f(50,50));
   button_2.setPosition(pos.x + 178, pos.y + 14);
   
   button_3.setSize(sf::Vector2f(50,50));
   button_3.setPosition(pos.x + 234, pos.y + 14);
   
   button_4.setSize(sf::Vector2f(50,50));
   button_4.setPosition(pos.x + 290, pos.y + 14);
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

//Draw menu_bar
void Int_button::draw(sf::RenderWindow& window)
{
  window.draw(menu_bar);
}
	


