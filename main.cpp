#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "Game.h"


using namespace sf;

int main()
{

    //Init game engine
    Game game;

    game.running();

    return 0;

}
