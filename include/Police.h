#ifndef POLICE_H
#define POLICE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Police
{
    public:
        Police(float posX, float posY);
        virtual ~Police();

    //Accessor
    const FloatRect getBounds() const;

    //Functions
    void update();
    void render(RenderTarget* target);

    protected:

    private:
        Texture texture;
        Sprite sprite;

        float speed;

    //Private functions
    void initVariables();
    void initTexture();
    void initSprite();
};

#endif // POLICE_H
