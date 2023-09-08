#ifndef MISSILE_H
#define MISSILE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;

class Missile
{
    public:
        Missile();
        Missile(Texture* texture, float posX, float posY, float dirX, float dirY, float movement_speed);
        virtual ~Missile();

    //Accessor
    const FloatRect getBounds() const;

    //Functions
    void update();
    void render(RenderTarget* target);

    protected:

    private:
        Sprite sprite;

        Vector2f direction;
        float movementSpeed;
};

#endif // MISSILE_H
