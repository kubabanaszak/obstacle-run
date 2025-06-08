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
    sf::Clock textureClock;
    float switchTime = 0.2;
    bool useFirstTexture = true;

public:
    std::string name;
    double result;
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
    friend std::ostream& operator<<(std::ostream&, const Player&);

};

class Text
{
protected:
    sf::Font font;
    sf::Text text;
    float size;

public:
    Text(float, float, float);
    Text(float, float, float, std::string);
    virtual ~Text();
    virtual void draw(sf::RenderWindow&);
    void setString(const std::string&);
    void SetFillColor(const sf::Color&);
    sf::FloatRect getGlobalBounds() const;
    void setPosition(float x, float y);

};

class HighScores 
{
private:
    std::vector<Text*> scores;

public:
    HighScores();
    ~HighScores();
    void draw(sf::RenderWindow&);

};


enum class MenuEvent
{
    None,
    StartGameClicked,
    HighScoresClicked,
    ExitClicked,
    BackClicked,
    NameEntered,
    NameInput,

}

class Menu
{
private:
    Text* item[4];
    Text* title;
    Text* playerText;
    Text* EnterName;
    sf::RectangleShape inputBox;
    std::string playerName;
    HighScores* highScores;

public:
    Menu();
    ~Menu();
    void draw(sf::RenderWindow&);
    void drawBox(sf::RenderWindow&);
    MenuEvent processEvent(sf::RenderWindow&, sf::Event&);
    bool isButtonClicked();
    bool showHighScores = false;
    bool buttonClicked = false;
    std::string getPlayerName();

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
Obstacle(float, float, const std::string&);
sf::RectangleShape shape;
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

class Game {
private:
    std::string GameName;
    float width, height;

    Player player;
    Menu menu;
    Score score;
    Text gameOverText;
    Text exitText;
    sf::Texture backgroundTexture;
    sf::Sprite background;

    sf::RenderWindow window;
    sf::Clock clock;
    sf::Clock scoreClock;

    std::vector<std::pair<Obstacle*, sf::Clock>> obstacles;

    int currentID;
    std::vector<double> topScores;

    bool gameOver;
    bool moveLeft;
    bool moveRight;
    bool gameStarted;

    void handleEvents();
    void update();
    void render();
    void movement();
    void los();

public:
    Game(float, float, std::string);
    ~Game();
    void run();
    void generateID();
    void getData();
    void savePlayerData();
    void loadScores();
    void sortScores();
    void saveScores();

};
#endif // KLASY_H
