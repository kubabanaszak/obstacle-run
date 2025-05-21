#include "klasy.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <fstream>

Player::Player() 
{
    shape.setSize(sf::Vector2f(100, 100));
    t[0].loadFromFile("bieg_1.png");
    t[1].loadFromFile("bieg_2.png");
    t[2].loadFromFile("skok.png");
    t[3].loadFromFile("wslizg.png");
    t[4].loadFromFile("emoji.png");
    shape.setTexture(&t[0]);
}

Player::~Player() {}

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

Text::Text(float s, float x, float y)
{
    size = s;
    font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::White);
    text.setPosition(x, y);
}

Text::~Text() {}

void Text::draw(sf::RenderWindow& window) { window.draw(text); }

Menu::Menu() {}
Menu::~Menu() {}

Score::Score() : Text(24, 10, 850) {}

Score::~Score() {};

void Score::Showscore(sf::Clock& scoreClock)
{
    elapsed = scoreClock.getElapsedTime();
    std::ostringstream oss;
    oss << "Score: " << elapsed.asMilliseconds();
    text.setString(oss.str());
}

int Score::getScore() { return elapsed.asMilliseconds(); }

Obstacle::Obstacle(){}
Obstacle::~Obstacle() {}

Up::Up() : Obstacle() {}
Up::~Up() {}

Down::Down() : Obstacle() {}
Down::~Down() {}

Both::Both() : Obstacle() {}
Both::~Both() {}

HighScore::HighScore() {}
HighScore::~HighScore() {}

PowerUp::PowerUp() {}
PowerUp::~PowerUp() {}

Game::Game() {}
Game::~Game() {}

void Game::generateID() 
{
    std::ifstream file("baza.txt");
    if (!file.is_open()) {
        currentID = 1;
        return;
    }
    std::string lastLine;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty())
            lastLine = line;
    }
    file.close();
    if (lastLine.empty()) {
        currentID = 1;
        return;
    }
    std::istringstream iss(lastLine);
    int lastID;
    if (iss >> lastID) {
        currentID = lastID + 1;
    }
    else {
        currentID = 1; 
    }
}

void Game::getData() 
{
    player.setID(currentID);
    player.nazwa = menu.getPlayerName();
    player.wynik = score.wynik;
}

void Game::savePlayerData() 
{
    if (!gameStarted || !gameOver) return;
    fstream file("baza.txt", ios::app);
    if (file.is_open()) {
        file << player;
        file.close();
    }
}

void Game::loadScores() 
{
    fstream file("wyniki.txt", ios::in);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line))
        {
            double d_line = std::stod(line);
            topScores.emplace_back(d_line);
        }
        file.close();
    }
    else {
        for (int i = 0; i < 3; i++)
        {
            topScores.emplace_back(0);
        }
    }
}

void Game::sortScores()
{
    topScores.emplace_back(player.wynik);
    std::sort(topScores.begin(), topScores.end());
}

void Game::saveScores() 
{
    if (!gameStarted || !gameOver) return;
    fstream plik("wyniki.txt", ios::out);
    if (plik.is_open()) {
        for (int i = 3; i > 0; i--) {
            plik << topScores[i] << "\n";
        }
        plik.close();
    }
}
