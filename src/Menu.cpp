#include "menu.hpp"
using namespace sf;
Menu::Menu(sf::Vector2u sizeW, std::string title, std::vector<std::string> itemsText)
{
    this->width = sizeW.x;
    this->height = sizeW.y;
    if (!menuMusic.openFromFile("Audio/Menu.ogg"))
        throw "Can't play menu music!";
    this->menuMusic.setLoop(true);
    this->menuMusic.play();
    this->menuFont.loadFromFile("Font/Antique Olive Std Nord Italic.otf");
    this->menuItemFont.loadFromFile("Font/Antique Olive Std Nord Italic.otf");
    this->menuTitle.setString(title);
    this->menuTitle.setFont(this->menuFont);
    this->menuTitle.setCharacterSize(128);
    this->menuTitle.setStyle(Text::Bold);
    this->menuTitle.setFillColor(Color::Blue);
    this->menuTitle.setPosition(sf::Vector2f((this->width/2)-(this->menuTitle.getLocalBounds().width/2),
                        (this->height/2)-(150*0.75)-200));
    this->itemChoosed = 1;
    for(int i = 0; i < itemsText.size(); i++) {
        sf::Text myitem;
        myitem.setString(itemsText[i]);
        myitem.setFont(this->menuItemFont);
        if (i == this->itemChoosed-1)
            myitem.setCharacterSize(72);
        else
            myitem.setCharacterSize(56);
        myitem.setStyle(sf::Text::Bold);
        myitem.setFillColor(sf::Color::Green);
        myitem.setPosition(sf::Vector2f((this->width/2)-100-(myitem.getLocalBounds().width/2),
                            (this->height/2)-(150*0.75)+100+(i*100)));
        this->menuItems.push_back(myitem);
}
//Arrow
if (!this->menuArrowTexture.loadFromFile("Texture/arrow.png"))
    throw "Can't load arrow image!";

sf::Sprite leftArrow;
    leftArrow.setTexture(this->menuArrowTexture);
    leftArrow.scale(sf::Vector2f(0.1,0.1));
    leftArrow.setColor(sf::Color(255, 255, 255, 255));
    leftArrow.setPosition(sf::Vector2f((this->width/2)-100+(this->menuItems[this->itemChoosed-1].getLocalBounds().width/2)+100,
                            (this->height/2)-(150*0.75)+100+((this->itemChoosed-1)*100)));
this->menuArrowSprite.push_back(leftArrow);

void Menu::draw(RenderWindow *window)
{
    window->draw(this->menuTitle);
    for(sf::Text item : this->menuItems)
        window->draw(item);
    for(sf::Sprite item : this->menuArrowSprite)
        window->draw(item);
}

void Menu::processEvents(sf::Event event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        this->itemChoosed += 1;
        if (this->itemChoosed > this->menuItems.size())
            this->itemChoosed = 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        this->itemChoosed -= 1;
        if (this->itemChoosed == 0)
            this->itemChoosed = this->menuItems.size();
    }
     // update menu
    for(int i = 0; i < this->menuItems.size(); i++) {
        if (i == this->itemChoosed-1)
            this->menuItems[i].setCharacterSize(72);
        else
            this->menuItems[i].setCharacterSize(56);
        this->menuItems[i].setPosition(sf::Vector2f((this->width/2)-100-(this->menuItems[i].getLocalBounds().width/2),
                        (this->height/2)-(150*0.75)+100+(i*100)));
    }

    // update arrow
    this->menuArrowSprite[0].setPosition(sf::Vector2f((this->width/2)-100+(this->menuItems[this->itemChoosed-1].getLocalBounds().width/2)+100,
                        (this->height/2)-(150*0.75)+100+((this->itemChoosed-1)*100)));
    this->menuArrowSprite[1].setPosition(sf::Vector2f((this->width/2)-100-(this->menuItems[this->itemChoosed-1].getLocalBounds().width/2)-100,
                        (this->height/2)-(150*0.75)+100+((this->itemChoosed-1)*100)));
}

/*Menu::Menu(sf::Vector2u sizeW, std::string title, std::vector<std::string> itemsText)
{
    this->width = sizeW.x;
    this->height = sizeW.y;
    if (!menuMusic.openFromFile("menu-music.ogg"))
        exit(-1);
    this->menuMusic.setLoop(true);
    this->menuMusic.play();
    this->menuFont.loadFromFile("Childhood-Bold.ttf");
    this->menuItemFont.loadFromFile("Tomodachy.ttf");
    this->menuTitle.setString(title);
    this->menuTitle.setFont(this->menuFont);
    this->menuTitle.setCharacterSize(128);
    this->menuTitle.setStyle(sf::Text::Bold);
    this->menuTitle.setFillColor(sf::Color::Green);
    this->menuTitle.setPosition(sf::Vector2f((this->width/2)-(this->menuTitle.getLocalBounds().width/2),
                        (this->height/2)-(150*0.75)-200));

    this->itemChoosed = 1;
    for(int i = 0; i < itemsText.size(); i++) {
        sf::Text myitem;
        myitem.setString(itemsText[i]);
        myitem.setFont(this->menuItemFont);
        if (i == this->itemChoosed-1)
            myitem.setCharacterSize(72);
        else
            myitem.setCharacterSize(56);
        myitem.setStyle(sf::Text::Bold);
        myitem.setFillColor(sf::Color::Green);
        myitem.setPosition(sf::Vector2f((this->width/2)-100-(myitem.getLocalBounds().width/2),
                            (this->height/2)-(150*0.75)+100+(i*100)));
        this->menuItems.push_back(myitem);
    }

    // load arrow image
    if (!this->menuArrowTexture.loadFromFile("pngguru.com.png")) {
        std::cout << "Error loading Arrow image ... " << std::endl;
        exit(-1);
    }

    sf::Sprite leftArrow, rightArrow;
    leftArrow.setTexture(this->menuArrowTexture);
    leftArrow.scale(sf::Vector2f(0.1,0.1));
    leftArrow.setColor(sf::Color(255, 255, 255, 255));
    leftArrow.setPosition(sf::Vector2f((this->width/2)-100+(this->menuItems[this->itemChoosed-1].getLocalBounds().width/2)+100,
                            (this->height/2)-(150*0.75)+100+((this->itemChoosed-1)*100)));
    rightArrow.setTexture(this->menuArrowTexture);
    rightArrow.scale(sf::Vector2f(-0.1,0.1));
    //rightArrow.rotate(180.0f);
    rightArrow.setColor(sf::Color(255, 255, 255, 255));
    rightArrow.setPosition(sf::Vector2f((this->width/2)-100-(this->menuItems[this->itemChoosed-1].getLocalBounds().width/2)-100,
                            (this->height/2)-(150*0.75)+100+((this->itemChoosed-1)*100)));
    this->menuArrowSprite.push_back(leftArrow);
    this->menuArrowSprite.push_back(rightArrow);
}

void Menu::draw(sf::RenderWindow *window)
{
    window->draw(this->menuTitle);
    for(sf::Text item : this->menuItems)
        window->draw(item);
    for(sf::Sprite item : this->menuArrowSprite)
        window->draw(item);
}


void Menu::processEvents(sf::Event event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        this->itemChoosed += 1;
        if (this->itemChoosed > this->menuItems.size())
            this->itemChoosed = 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        this->itemChoosed -= 1;
        if (this->itemChoosed == 0)
            this->itemChoosed = this->menuItems.size();
    }

    // update menu
    for(int i = 0; i < this->menuItems.size(); i++) {
        if (i == this->itemChoosed-1)
            this->menuItems[i].setCharacterSize(72);
        else
            this->menuItems[i].setCharacterSize(56);
        this->menuItems[i].setPosition(sf::Vector2f((this->width/2)-100-(this->menuItems[i].getLocalBounds().width/2),
                        (this->height/2)-(150*0.75)+100+(i*100)));
    }

    // update arrow
    this->menuArrowSprite[0].setPosition(sf::Vector2f((this->width/2)-100+(this->menuItems[this->itemChoosed-1].getLocalBounds().width/2)+100,
                        (this->height/2)-(150*0.75)+100+((this->itemChoosed-1)*100)));
    this->menuArrowSprite[1].setPosition(sf::Vector2f((this->width/2)-100-(this->menuItems[this->itemChoosed-1].getLocalBounds().width/2)-100,
                        (this->height/2)-(150*0.75)+100+((this->itemChoosed-1)*100)));
}
*/
