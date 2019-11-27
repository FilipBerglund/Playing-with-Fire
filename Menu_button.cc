#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include "Menu_button.h"

Menu_button::Menu_button()
{
}

Start_button::Start_button()
{
}


Start_button::Start_button(sf::Vector2f pos, sf::Texture s):
  sprite{s}
{
  sprite.setPosition(pos);
}

//Kollar om musen är på bool button
bool Start_button::click(sf::Mouse& mouse)
{
  if (sprite.getGlobalBounds().contains(mouse.getPosition().x , mouse.getPosition().y))
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


Int_button::Int_button(sf::Vector2f pos, sf::Texture s0, sf::Texture s1,
		        sf::Texture s2,   sf::Texture s3, sf::Texture s4,
		        sf::Texture sbg )
  : sprite0{s0}, sprite1{s1}, sprite2{s2}, sprite3{s3},
    sprite4{s4}, sprite_background{sbg} , value{0}
 {
  float corrdx{};
  float corrdy{};
  corrdx = pos.x;
  corrdy = pos.y;
  
  //back grunds lådan
  sprite_background.setPosition(pos);
  //sprite0 lådan
  sprite0.setPosition(sf::Vector2f(corrdx+50, corrdy+100));
  //sprite1  lådan
  sprite1.setPosition(sf::Vector2f(corrdx+100, corrdy+100));
  //sprite2  lådan
  sprite2.setPosition(sf::Vector2f(corrdx+150, corrdy+100));
  //sprite3  lådan
   sprite3.setPosition(sf::Vector2f(corrdx+200, corrdy+100));
  //sprite4  lådan 
  sprite4.setPosition(sf::Vector2f(corrdx+250, corrdy+100));
 }

// KOllar vilken låda musen är över och anger rätt value				     
bool Int_button::click(sf::Mouse& mouse)
{
  if (sprite0.getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y))
    {
      value = 0;
      return true;
    }
  else if(sprite1.getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y))
    {
      value = 1;
      return true;
    }
  else if(sprite2.getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y))
      {
	value = 2;
	return true;
      }
  else if(sprite3.getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y))
	{
	  value = 3;
	  return true;
	}
  else if(sprite4.getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y))
	  {
	    value = 4;
	    return true;
	  }
	  else
	    {
	      return false;
	    }
}

//Ritar Int_button
void Int_button::draw(sf::RenderWindow& window)
{
  window.draw(sprite_background);
  window.draw(sprite0);
  window.draw(sprite1);
  window.draw(sprite2);
  window.draw(sprite3);
  window.draw(sprite4);
}

	


