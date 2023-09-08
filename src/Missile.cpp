#include "Missile.h"

using namespace sf;
using namespace std;

Missile::Missile()
{
    //ctor
}

Missile::Missile(Texture * texture, float posX, float posY, float dirX, float dirY, float movement_speed)
{
    this->sprite.setTexture(*texture);
    this->sprite.scale(0.05f,0.05f);
    this->sprite.setPosition(posX, posY);
    this->direction.x = dirX;
    this->direction.y = dirY;
    this->movementSpeed = movement_speed;
}

Missile::~Missile()
{
    //dtor
}

//Accessor
    const FloatRect Missile::getBounds() const
    {
        return this->sprite.getGlobalBounds();
    }

 //Functions
    void Missile::update()
    {
        this->sprite.move(this->movementSpeed * this->direction);
    }
    void Missile::render(RenderTarget * target)
    {
        target->draw(this->sprite);
    }
