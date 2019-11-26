#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include "Menu_button.h"

Menu_button::Menu_button()
{
}


Menu_button::Menu_button(sf::Vector2f pos, sf::Sprite s):
  sprite{s}
{
  sprite.setPosition(pos);
  sf::RectangleShape shape;
  shape.setSize(sf::Vector2f(100, 100));
  shape.setPosition(pos);
}




Int_button::Int_button(sf::Vector2f pos, sf::Texture s0, sf::Texture s1, sf::Texture s2, sf::Texture s3, sf::Texture s4 , sf::Texture sbg )
  : sprite0{s0}, sprite1{s1}, sprite2{s2}, sprite3{s3}, sprite4{s4}, sprite_background{sbg} , value{0}
 {
  float corrdx{};
  float corrdy{};
  corrdx = pos.x;
  corrdy = pos.y;
  
  //back grunds lådan
  //fixa corrdinter senare
  sprite_background.setPosition(pos);
  //sf::RectangleShape shape_sprite_background;
  //shape_sprite_background.setSize(sf::Vector2f(sprite_background.getSize()));
  //shape_sprite_background.setPosition(pos);

  //sprite0 lådan
  sprite0.setPosition(sf::Vector2f(corrdx+50,corrdy+100));
  //sf::RectangleShape shape_sprite0;
  //shape_sprite0.setSize(sf::Vector2f(sprite0.getSize()));
  //shape_sprite0.setPosition(corrdx+50,corrdy+100);
  
  //sprite1  lådan
  //fixa corrdinter senare 
  sprite1.setPosition(sf::Vector2f(corrdx+50,corrdy+100));
  //sf::RectangleShape shape_sprite1;
  //shape_sprite1.setSize(sf::Vector2f(sprite2.getSize()));
  //shape_sprite1.setPosition(corrdx+50,corrdy+100);
  
  //sprite2  lådan
  //fixa corrdinter senare 
  sprite2.setPosition(sf::Vector2f(corrdx+50,corrdy+100));
  //sf::RectangleShape shape_sprite2;
  //shape_sprite2.setSize(sf::Vector2f(sprite3.getSize()));
  //shape_sprite2.setPosition(corrdx+50,corrdy+100);
  
  //sprite3  lådan
  //fixa corrdinter senare
   sprite3.setPosition(sf::Vector2f(corrdx+50,corrdy+100));
  //sf::RectangleShape shape_sprite3;
  // shape_sprite3.setSize(sf::Vector2f((sprite3.getSize()));
  // shape_sprite3.setPosition(corrdx+50,corrdy+100);

  //sprite4  lådan 
  sprite4.setPosition(sf::Vector2f(corrdx+50,corrdy+100));
  //sf::RectangleShape shape_sprite4;
  //shape_sprite4.setSize(sf::Vector2f(sprite4.getSize()));
  // shape_sprite4.setPosition(corrdx+50,corrdy+100);
  
  
 }

				     
bool Int_button::click(sf::Mouse& mouse)
{
  if (sprite0.getGlobalBounds().contains(mouse.getPosition().x , mouse.getPosition().y))
    {
      value = 0;
      return true;
    }
  else if(sprite1.getGlobalBounds().contains(mouse.getPosition().x , mouse.getPosition().y))
    {
      value = 1;
      return true;
    }
  else if(sprite2.getGlobalBounds().contains(mouse.getPosition().x , mouse.getPosition().y))
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

	


