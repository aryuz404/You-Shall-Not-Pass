#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;

class Player
{
    public:
        Player();
        virtual ~Player();

    //Accessor
    const Vector2f& getPos() const;
    const FloatRect getBounds() const;
    const int& getHP() const;
    const int& getHPMax() const;

    //Modifiers
    void setPosition(const float x, const float y);
    void setHP(const int hp);
    void loseHP(const int value);

    //Functions
    void move(const float dirX, const float dirY);
    const bool canAttack();

    void updateAttack();
    void update();
    void render(RenderTarget& target);

    protected:

    private:
        Texture texture;
        Sprite sprite;

        //HP
        int hp;
        int hpMax;


        float movementSpeed;
        float attackCooldown;
        float attackCooldownMax;


    //Private functions
    void initVariables();
    void initTexture();
    void initSprite();
};

#endif //PLAYER_H
