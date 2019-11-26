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

bool Menu_button::contains(sf::Mouse&)
{
  if(shape.getGlobalbounds)
    {
      return true;
    }
  else
    {
      return false;
    }
}

int Menu_button::click(sf::Mouse&)
{
  // click returnera än int beroende på hur många npcs som skata med;
  /*
  if (spritezero.contatins(mouse.x, mouse.y))
    {
      return 0;
    }
  */
  if()
    {
    }
  
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
  sprite_backgroud.setPosition(pos);
  sf::RectangleShape shape_sprite_background;
  shape_sprite_background.setSize(sf::Vector2f(sprite_background.getsize()));
  shape_sprite_background.setPosition(pos);

  //sprite0 lådan
  sprite0.setPosition(sf::Vector2f(corrdx+50,corrdy+100));
  sf::RectangleShape shape_0;
  shape_sprite0.setSize(sf::Vector2f(sprite0.getsize());
  shape_sprite0.setPosition(corrdx+50,corrdy+100);
  
  //sprite1  lådan
  //fixa corrdinter senare 
  sprite1.setPosition(sf::Vector2f(corrdx+50,corrdy+100));
  sf::RectangleShape shape_1;
  shape_sprite1.setSize(sf::Vector2f(sprite1.getsize());
  shape_sprite1.setPosition(corrdx+50,corrdy+100);

  //sprite1  lådan
  //fixa corrdinter senare 
  sprite1.setPosition(sf::Vector2f(corrdx+50,corrdy+100));
  sf::RectangleShape shape_1;
  shape_sprite1.setSize(sf::Vector2f(sprite2.getsize());
  shape_sprite1.setPosition(corrdx+50,corrdy+100);
  //sprite2  lådan
  //fixa corrdinter senare 
  sprite2.setPosition(sf::Vector2f(corrdx+50,corrdy+100));
  sf::RectangleShape shape_2;
  shape_sprite2.setSize(sf::Vector2f(sprite3.getsize());
  shape_sprite2.setPosition(corrdx+50,corrdy+100);
  //sprite3  lådan
  //fixa corrdinter senare 
  sprite3.setPosition(sf::Vector2f(corrdx+50,corrdy+100));
  sf::RectangleShape shape_3;
  shape_sprite3.setSize(sf::Vector2f((sprite3.getsize());
  shape_sprite3.setPosition(corrdx+50,corrdy+100);

  //sprite4  lådan
  //fixa corrdinter senare 
  sprite4.setPosition(sf::Vector2f(corrdx+50,corrdy+100));
  sf::RectangleShape shape_4;
  shape_sprite4.setSize(sf::Vector2f(sprite4.getsize());
  shape_sprite4.setPosition(corrdx+50,corrdy+100);
  
  
 }

bool Int_button::click(sf::Mouse&)
{
  if (sprite0.contains(mouse.x, mouse.y))
    {
      value = 0;
      return true;
    }
  else if(sprite1.contains(mouse.x, mouse.y)
    {
      value = 1;
      return true;
    }
    else if(sprite2.contains(mouse.x, mouse.y)
      {
	value = 2;
	return true;
      }
      else if(sprite3.contains(mouse.x, mouse.y)
	{
	  value = 3;
	  return true;
	}
	else if(sprite4.contains(mouse.x, mouse.y)
	  {
	    value = 4;
	    return true;
	  }
	  else
	    {
	      return false;
	    }


}



