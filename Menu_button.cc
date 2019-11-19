
Menu_button::Menu_button()
{
}


Menu_button::Menu_button(sf::Vector2f pos, sf::Sprite s):
  sprite{s}
{
  sprite.setPosition(pos);
}

bool Menu_button::contains(sf::Mouse&)
{
  // Kollar om musen är på meubutton
  
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
  
}


Int_button::Int_button(sf::Vector2f pos, sf::Sprite s0, sf::Sprite s1, sf::Sprite s2, sf::Sprite s3, sf::Sprite s4 , sf::Sprite sbg ):
  sprite0{s0}, sprite1{s1}, sprite2{s2}, sprite3{s3}, sprite4{s4}, sprite_background{sbg}
{
  sprite_backgroud.setPosition(pos);
  // Fixa ritningen så att det ritas relativt sprite background
  
}
Int_button::click(sf::Mouse&)
{
  if ()
    {}
  
}

