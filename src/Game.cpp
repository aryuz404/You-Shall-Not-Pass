#include "Game.h"
#include <iostream>

using namespace sf;
using namespace std;


//Private functions
void Game::initWindow()
{
    this->window = new RenderWindow(VideoMode(800,500), "You Shall Not Pass!");
    this->window->setFramerateLimit(60);

}

void Game::initTextures()
{
    this->textures["Missile"] = new Texture();
    this->textures["Missile"]->loadFromFile("Texture/rocket.png");
}

void Game::initUI()
{
    //Load font
    if(!this->font.loadFromFile("Font/needforspeed.ttf"))
        cout << "ERROR::CAN'T LOAD FONT!!" << "\n";

    //Init score text
    this->scoreText.setPosition(480.f,3.f);
    this->scoreText.setFont(this->font);
    this->scoreText.setCharacterSize(28);
    this->scoreText.setOutlineThickness(3.f);
    this->scoreText.setOutlineColor(Color::Black);
    this->scoreText.setFillColor(Color::Red);

    //Hp
    this->hpText.setPosition(20.f,3.f);
    this->hpText.setFont(this->font);
    this->hpText.setCharacterSize(28);
    this->hpText.setOutlineThickness(3.f);
    this->hpText.setOutlineColor(Color::Black);
    this->hpText.setFillColor(Color::Red);
    this->hpText.setString("HP ");

    //Game Ova
    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(60);
    this->gameOverText.setFillColor(Color::Red);
    this->gameOverText.setOutlineThickness(5.f);
    this->gameOverText.setOutlineColor(Color::Black);
    this->gameOverText.setString("Game Over ");
    this->gameOverText.setPosition(this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
                                   this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

    //Quit
    this->quitText.setFont(this->font);
    this->quitText.setCharacterSize(24);
    this->quitText.setFillColor(Color::Red);
    this->quitText.setString("Press Esc to Quit Game");
    this->quitText.setPosition(this->gameOverText.getPosition().x + 20.f,
                                   this->gameOverText.getPosition().y + 70.f);

    //Player HP
    this->hpBar.setSize(Vector2f(300.f, 20.f));
    this->hpBar.setFillColor(Color::Red);
    this->hpBar.setOutlineColor(Color::Black);
    this->hpBar.setOutlineThickness(2.f);
    this->hpBar.setPosition(Vector2f (90.f,10.f));

    this->hpBarBack = this->hpBar;
    this->hpBarBack.setFillColor(Color(25, 25, 25, 200));
}

void Game::initRoad()
{
    if(!this->roadTex.loadFromFile("Texture/road.png"))
    {
        cout << "ERROR::CAN'T LOAD ROAD TEXTURE!!" << "\n";
    }

    this->road.setTexture(this->roadTex);
    this->road.setScale(Vector2f(0.695f,0.695f));
}

void Game::initSystem()
{
    this->score = 0;
}

void Game::initPlayer()
{
    this->player = new Player();
}

void Game::initPolice()
{
    this->policeSpawnTimerMax = 40.f;
    this->policeSpawnTimer = this->policeSpawnTimerMax;
}

void Game::initMusic()
{
    //BGM
    if(!this->music.openFromFile("Audio/Arknights.ogg"))
    {
        cout << "ERROR::NO SANITY, DOKUTA!!" << "\n";
    }
    this->music.setLoop(true);
    this->music.play();

    //Missile
    if(!this->missSound.loadFromFile("Audio/RocketLaunch.ogg"))
    {
        cout << "ERROR::CAN'T PLAY MISSILE SOUND!!" << "\n";
    }
    this->miss.setBuffer(this->missSound);
    this->miss.setVolume(80.f);

    //Explosion
    if(!this->explodeSound.loadFromFile("Audio/Explosion2.ogg"))
    {
        cout << "ERROR::CAN'T PLAY MEGUMIN SOUND!!" << "\n";
    }
    this->explode.setBuffer(this->explodeSound);
    this->explode.setVolume(60.f);

    //Police pass
    if(!this->policeSound.loadFromFile("Audio/policepass.ogg"))
    {
        cout << "ERROR::CAN'T PLAY POLICE PASS!!" << "\n";
    }
    this->polizia.setBuffer(this->policeSound);
    this->polizia.setVolume(70.f);

    //Crash sound
    if(!this->crashSound.loadFromFile("Audio/crash.ogg"))
    {
        cout << "ERROR::CAN'T PLAY CRASH!!" << "\n";
    }
    this->crash.setBuffer(this->crashSound);
    this->crash.setVolume(60.f);

    //Start & over sound
    if(!this->startSound.loadFromFile("Audio/Start.ogg"))
    {
        cout << "ERROR::CAN'T PLAY START SOUND!!" << "\n";
    }
    this->start.setBuffer(this->startSound);
    this->start.setVolume(80.f);

    if(!this->overSound.loadFromFile("Audio/Over.ogg"))
    {
        cout << "ERROR::CAN'T PLAY OVER SOUND!!" << "\n";
    }
    this->over.setBuffer(this->overSound);
    this->over.setVolume(80.f);

}

//Constructor / Destructor
Game::Game()
{
    //ctor
    this->initWindow();
    this->initTextures();
    this->initUI();
    this->initRoad();
    this->initSystem();
    this->initMusic();

    this->initPlayer();
    this->initPolice();
}

Game::~Game()
{
    //dtor
    delete this->window;
    delete this->player;

    //Delete texture
    for (auto &i : this->textures)
    {
        delete i.second;  //Deleting all the texture that appear at the second time
    }

    //Delete missile
    for (auto *i : this->missiles)
    {
        delete i;
    }

    //Delete police
    for (auto *i : this->polices)
    {
        delete i;
    }
}

//Functions
void Game::running()
{
    this->start.play();
    while(this->window->isOpen())
    {
        this->pollEvents();

        if (this->player->getHP() > 0)
            this->update();

        this->render();
    }
}

void Game::pollEvents()
{
        while(this->window->pollEvent(this->eve))
        {
            switch(this->eve.type)
            {
            case Event::Closed:
                this->window->close();
                break;
            case eve.KeyPressed:
                if (this->eve.key.code == Keyboard::Escape)
                this->window->close();
                break;

            }
        }
}

void Game::updateInput()
{
   //Move player
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        this->player->move(-1.f,0.f);
    }

    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        this->player->move(1.f,0.f);
    }

    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        this->player->move(0.f,-1.f);
    }

    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        this->player->move(0.f,1.f);
    }

    //Missile shoot
    if (Mouse::isButtonPressed(Mouse::Left) && this->player->canAttack())
    {
        this->miss.play();
        this->missiles.push_back(new Missile(this->textures["Missile"],
                this->player->getPos().x, this->player->getPos().y  + this->player->getBounds().height/2.f, 1.f, 0.f, 10.f));
    }
}

void Game::updateUI()
{
    stringstream ss;
    ss << "Score  :  "<< this->score;
    this->scoreText.setString(ss.str());

    //Player HP
    float hpPercent = static_cast<float> (this->player->getHP()) / this->player->getHPMax();
    this->hpBar.setSize(Vector2f(300.f * hpPercent, this->hpBar.getSize().y));
}

void Game::updateRoad()
{

}

void Game::updateCollision()
{
    //Left
    if (this->player->getBounds().left < 0.f)
    {
        this->player->setPosition(0.f, this->player->getBounds().top);
    }

    //Right
    else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
    {
        this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
    }

    //Up
    if (this->player->getBounds().top < 0.f)
    {
        this->player->setPosition(this->player->getBounds().left, 0.f);
    }

    //Down
    else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
    {
        this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
    }
}

void Game::updateMissile()
{
    unsigned counter = 0;
    for (auto *missile : this->missiles)
    {
         missile->update();

         //Missile not hit
         if (missile->getBounds().left > window->getSize().x)
         {
             //Delete missile
             delete this->missiles.at(counter);
             this->missiles.erase(this->missiles.begin() + counter);

         }
         ++counter;
    }
}

void Game::updatePolice()
{
    //Spawning
    this->policeSpawnTimer += 1.f;
    if (this->policeSpawnTimer >= this->policeSpawnTimerMax)
    {

        this->polices.push_back(new Police(900.f, rand()% this->window->getSize().y - 30.f));
        this->policeSpawnTimer = 0.f;
    }

    //Update
    unsigned counter = 0;
    for (auto *police : this->polices)
    {
         police->update();

         //Police pass
         if (police->getBounds().left + police->getBounds().width < 0 && police->getBounds().top > 0
             && police->getBounds().top + police->getBounds().height < this->window->getSize().y)
         {
             //Delete police
             delete this->polices.at(counter);
             this->polices.erase(this->polices.begin() + counter);

             this->player->loseHP(1);

             this->polizia.play();
         }
         //Police hit player
         else if (police->getBounds().intersects(this->player->getBounds()))
         {
             delete this->polices.at(counter);
             this->polices.erase(this->polices.begin() + counter);

             this->player->loseHP(1);

             this->crash.play();
         }
         ++counter;
    }

}

void Game::updateHit()
{
    for (int i = 0; i < this->polices.size(); ++i)
    {
        bool police_dead = false;
      for (size_t k = 0; k < this->missiles.size() && police_dead == false; k++)
      {
          if (this->polices[i]->getBounds().intersects(this->missiles[k]->getBounds()))
          {
              this->explode.play();

              this->score++;

              delete this->polices[i];
              this->polices.erase(this->polices.begin() + i);

              delete this->missiles[k];
              this->missiles.erase(this->missiles.begin() + k);

              police_dead = true;
          }
      }

    }

    //game over sound
    if (this->player->getHP() <= 0)
    {
        this->over.play();
    }
}


void Game::update()
{
    this->updateInput();

    this->player->update();

    this->updateCollision();

    this->updateMissile();

    this->updatePolice();

    this->updateHit();

    this->updateUI();

    this->updateRoad();

}

void Game::renderUI()
{
    this->window->draw(this->scoreText);
    this->window->draw(this->hpText);
    this->window->draw(this->hpBarBack);
    this->window->draw(this->hpBar);
}

void Game::renderRoad()
{
    this->window->draw(this->road);
}

void Game::render()
{
    /*
    @return void
    -clear old frame
    -render object
    -display frame in window
    Render game object
    */
    this->window->clear();

    //Draw road
    this->renderRoad();

    //Draw anything
    this->player->render(*this->window);    //Put * to dereference

    for (auto *missile : this->missiles)
    {
        missile->render(this->window);
    }

    for (auto *police : this->polices)
    {
        police->render(this->window);
    }

    this->renderUI();

    //Game over screen
    if (this->player->getHP() <= 0)
    {
        this->window->draw(this->gameOverText);
        this->window->draw(this->quitText);

        this->music.stop();

    }

    this->window->display();
}
