#include "Police.h"

using namespace sf;
using namespace std;

//Private functions
void Police::initVariables()
{
    this->speed = -8.f;
}

void Police::initTexture()
{
    //Load texture from file
    if(!this->texture.loadFromFile("Texture/police.png"))
    {
        cout << "ERROR::CAN'T LOAD POLICE TEXTURE!!" << "\n";
    }

}

void Police::initSprite()
{
    //Set sprite from texture
    this->sprite.setTexture(this->texture);

    //Resize
    this->sprite.scale(0.3f,0.3f);

}

Police::Police(float posX, float posY)
{
    //ctor
    this->initVariables();
    this->initTexture();
    this->initSprite();

    this->sprite.setPosition(posX, posY);
}

Police::~Police()
{
    //dtor
}

//Accessor
const FloatRect Police::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

//Functions
void Police::update()
{
    this->sprite.move(this->speed, 0.f);
}

void Police::render(RenderTarget* target)
{
    target->draw(this->sprite);
}
