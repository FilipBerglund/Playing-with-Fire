#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H
#include <SFML/Graphics.hpp>


class Menu_button
{
public:
    virtual ~Menu_button() = default;
    virtual bool click(sf::Mouse&, sf::RenderWindow&)=0;
    virtual void draw(sf::RenderWindow&)=0;
};

class Start_button : public Menu_button
{
public:
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
    Int_button(sf::Vector2f, sf::Texture&);
    bool click(sf::Mouse&, sf::RenderWindow&) override;
    void draw(sf::RenderWindow&) override;
    int get_value() const {return value;}

private:
    sf::Sprite menu_bar;
    int value;
    sf::Vector2f bsize{50,50};
    sf::RectangleShape button_0;
    sf::RectangleShape button_1;
    sf::RectangleShape button_2;
    sf::RectangleShape button_3;
    sf::RectangleShape button_4;
};

#endif
