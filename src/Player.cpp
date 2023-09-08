#include "Player.h"

using namespace sf;
using namespace std;

//Private functions
void Player::initVariables()
{
    this->movementSpeed = 10.f;
    this->attackCooldownMax = 5.f;
    this->attackCooldown = this->attackCooldownMax;

    this->hpMax = 10;
    this->hp = this->hpMax;
}


void Player::initTexture()
{
    //Load texture from file
    if(!this->texture.loadFromFile("Texture/player.png"))
    {
        cout << "ERROR::CAN'T LOAD PLAYER TEXTURE!!" << "\n";
    }
}

void Player::initSprite()
{
    //Set sprite from texture
    this->sprite.setTexture(this->texture);

    //Resize
    this->sprite.scale(0.15f,0.15f);
}


//Constructor / Destructor
Player::Player()
{
    //ctor

    this->initVariables();
    this->initTexture();
    this->initSprite();
}

Player::~Player()
{
    //dtor
}

//Accessor
    const Vector2f& Player::getPos() const
    {
        return this->sprite.getPosition();
    }

    const FloatRect Player::getBounds() const
    {
        return this->sprite.getGlobalBounds();
    }

    const int& Player::getHP() const
    {
        return this->hp;
    }

    const int& Player::getHPMax() const
    {
        return this->hpMax;
    }

//Modifiers
    void Player::setPosition(const float x, const float y)
    {
        this->sprite.setPosition(x, y);
    }

    void Player::setHP(const int hp)
    {
        this->hp = hp;
    }
    void Player::loseHP(const int value)
    {
        this->hp -= value;

        if (this->hp < 0)
            this->hp = 0;
    }
//Functions
void Player::move(const float dirX, const float dirY)
{
    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canAttack()
{
    if (this->attackCooldown >= this->attackCooldownMax)
    {
        this->attackCooldown = 0.f;
        return true;
    }
    return false;
}

void Player::updateAttack()
{
    if (this->attackCooldown < this->attackCooldownMax)
        this->attackCooldown += 0.2f;
}

void Player::update()
{
    this->updateAttack();
}

void Player::render(RenderTarget& target)
{
    target.draw(this->sprite);
}
