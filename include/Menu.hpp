#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include <iostream>
#include <bits/stdc++.h>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Menu {
private:
    sf::Music menuMusic;
    sf::Font menuFont, menuItemFont;
    sf::Text menuTitle;
    std::vector<sf::Text> menuItems;
    sf::Texture menuArrowTexture;
    std::vector<sf::Sprite> menuArrowSprite;
    int width, height;
    int itemChoosed;

public:
    Menu(sf::Vector2u sizeW, std::string title, std::vector<std::string> itemsText);
    void draw(sf::RenderWindow *window);
    void processEvents(sf::Event event);
};

#endif // MENU_HPP_INCLUDED
