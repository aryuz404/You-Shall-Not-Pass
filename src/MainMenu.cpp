#include "MainMenu.h"

using namespace sf;
using namespace std;

MainMenu::MainMenu(float width, float height)
{
    //ctor
    if(!this->font.loadFromFile("Font/Antique Olive Std Nord Italic.otf"))
    {

    }

    menuText[0].setFont(font);
    menuText[0].setColor(Color::Red);
    menuText[0].setString("Play");
    menuText[0].setPosition(Vector2f(width / 2, height / (Max_Items + 1) * 1));

    menuText[1].setFont(font);
    menuText[1].setColor(Color::White);
    menuText[1].setString("Instruction");
    menuText[1].setPosition(Vector2f(width / 2, height / (Max_Items + 1) * 2));

    menuText[2].setFont(font);
    menuText[2].setColor(Color::White);
    menuText[2].setString("Quit");
    menuText[2].setPosition(Vector2f(width / 2, height / (Max_Items + 1) * 3));
}

MainMenu::~MainMenu()
{
    //dtor
}

//Functions
void MainMenu::draw(RenderWindow * window)
{
    for (int i = 0; i < Max_Items; i++)
    {
        window->draw(menuText[i]);
    }
}
