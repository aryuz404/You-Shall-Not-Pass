#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <string>
#include <sstream>
#include <vector>
#include "Player.h"
#include "Missile.h"
#include "Police.h"


using namespace sf;
using namespace std;

//Game engine class

class Game
{
    public:
        //Constructor / Destructor
        Game();
        virtual ~Game();

        //Functions
        void running();
        void pollEvents();
        void updateInput();
        void updateMissile();
        void updatePolice();
        void updateHit();
        void updateCollision();
        void updateUI();
        void updateRoad();
        void update();
        void renderUI();
        void renderRoad();
        void render();

    protected:

    private:
        //Window
        RenderWindow* window;
        Event eve;

        //Missile
        map <string, Texture*> textures;            //to map 2 things together, for each string there will be a texture
        vector <Missile*> missiles;

        //MusicBGM
        Music music;

        //Missile Sound
        SoundBuffer missSound;
        Sound miss;

        //Explosion Sound
        SoundBuffer explodeSound;
        Sound explode;

        //Police pass sound
        SoundBuffer policeSound;
        Sound polizia;

        //Crash sound
        SoundBuffer crashSound;
        Sound crash;

        //Start & game over sound
        SoundBuffer startSound;
        SoundBuffer overSound;

        Sound start;
        Sound over;

        //UI
        Font font;
        Text scoreText;

        Text hpText;

        Text gameOverText;

        Text quitText;

        //Background
        Texture roadTex;
        Sprite road;

        //System
        unsigned score;

        //Player
        Player* player;

        //PlayerHPbar
        RectangleShape hpBar;
        RectangleShape hpBarBack;

        //Police
        float policeSpawnTimer;
        float policeSpawnTimerMax;
        vector <Police*> polices;

        //Private functions
        void initWindow();
        void initTextures();
        void initUI();
        void initRoad();
        void initSystem();
        void initMusic();

        void initPlayer();
        void initPolice();
};

#endif // GAME_H
