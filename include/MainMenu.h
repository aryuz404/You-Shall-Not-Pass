#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#define Max_Items 3

using namespace sf;
using namespace std;

class MainMenu
{
    public:
        MainMenu(float width, float height);
        virtual ~MainMenu();

    //Functions
    void draw(RenderWindow *window);
    void MoveUp();
    void MoveDown();

    protected:

    private:
        Font font;
        Text menuText[Max_Items];

        int selectedItemsIndex;

    //Private functions
};

#endif // MAINMENU_H
