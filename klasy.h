#ifndef KLASY_H
#define KLASY_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <fstream>

class Player
{
private:
sf::Texture t[5];
sf::RectangleShape shape;
int ID;
float switchTime = 0.2;
bool useFirstTexture = true;

public:
string nazwa;
double wynik;
Player();
~Player();
void setID(int);
int getID();
void setPosition(float, float);
sf::Vector2f getPosition();
sf::RectangleShape& getShape();
void textureChange();
void endTexture();
void draw(sf::RenderWindow&);

};

class Text
{
protected:
sf::Font font;
sf::Text text;
float size;

public:
Text(float, float, float);
Text(float, float, float, string);
virtual ~Text();
virtual void draw(sf::RenderWindow&);

};

class Menu
{
private:
sf::Font font;
sf::Text item[itemCount];
sf::Text title;
sf::Text playerText;
sf::Text EnterName;
sf::RectangleShape inputBox;
string playerName;
bool buttonClicked = false;

public:
void draw(sf::RenderWindow&);
void drawBox(sf::RenderWindow&);
Menu();
~Menu();
string getPlayerName();

};

class Score : public Text
{
private:
sf::Time elapsed;

public:
int wynik;
Score();
~Score();
void Showscore(sf::Clock&);
int getScore();
   
};

class Obstacle
{
protected:
sf::Texture texture;
float width, height;
string textureFile;
    
public:
Obstacle(float, float, const string&);
virtual ~Obstacle();
virtual void setPosition(float, float);
virtual void draw(sf::RenderWindow&);
virtual bool checkCollision(Player& player) = 0;

};

class Up : public Obstacle
{
public:
Up();
~Up();
bool checkCollision(Player&);

};

class Down : public Obstacle
{
public:
Down();
~Down();
bool checkCollision(Player&);

};

class Both : public Obstacle
{
public:
Both();
~Both();
bool checkCollision(Player&);

};

class HighScore
{
private:

public:
HighScore();
~HighScore();

};

class PowerUp
{
public:
PowerUp();
~PowerUp();

};

class Game
{
private:
std::string GameName;
float width, height;
Score score;
Player player;
sf::RenderWindow window;
sf::Clock scoreClock;
int currentID;
std::vector<double> topScores;
bool gameOver;
bool gameStarted;

public:
Game();
~Game();
void generateID();
void getData();
void savePlayerData();
void loadScores();
void sortScores();
void saveScores();

};
#endif // KLASY_H
