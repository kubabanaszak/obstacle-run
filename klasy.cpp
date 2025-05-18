#include "klasy.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <fstream>

Game::Game() {};
Game::~Game() {};

Player::Player() 
{
    shape.setSize(sf::Vector2f(100, 100));
    t[0].loadFromFile("bieg_1.png");
    t[1].loadFromFile("bieg_2.png");
    t[2].loadFromFile("skok.png");
    t[3].loadFromFile("wslizg.png");
    t[4].loadFromFile("emoji.png");
    shape.setTexture(&t[0]);
};

Player::~Player() {};
void Player::setPosition(float x, float y) {shape.setPosition(x, y);}

sf::Vector2f Player::getPosition() {return shape.getPosition();}

sf::RectangleShape& Player::getShape() {return shape;}

void Player::textureChange()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        shape.setTexture(&t[2]);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        shape.setTexture(&t[3]);
    }
    if (textureClock.getElapsedTime().asSeconds() >= switchTime) {
        if (useFirstTexture) {
            shape.setTexture(&t[1]);
        }
         else
        {
            shape.setTexture(&t[0]);
        }
        useFirstTexture = !useFirstTexture;
        textureClock.restart();
    }
}
void Player::endTexture() {shape.setTexture(&t[4]);}

Text::Text() {};
Text::~Text() {};

Menu::Menu() {};
Menu::~Menu() {};

Score::Score() : Text() {};
Score::~Score() {};

Obstacle::Obstacle(){};
Obstacle::~Obstacle() {};

Up::Up() : Obstacle() {};
Up::~Up() {};

Down::Down() : Obstacle() {};
Down::~Down() {};

Both::Both() : Obstacle() {};
Both::~Both() {};

HighScore::HighScore() {};
HighScore::~HighScore() {};

PowerUp::PowerUp() {};
PowerUp::~PowerUp() {};
