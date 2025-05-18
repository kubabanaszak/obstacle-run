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

class Game
{
private:

public:
Game();
~Game();

};

class Player
{
private:

public:
Player();
~Player();

};

class Text
{
protected:

public:


};

class Menu
{
private:

public:
Menu();
~Menu();

};

class Score : public Text
{
private:

public:
Score();
~Score();
   
};

class Obstacle
{
protected:
    
public:

};

class Up : public Obstacle
{
public:
Up();
~Up();

};

class Down : public Obstacle
{
public:
Down();
~Down();

};

class Both : public Obstacle
{
public:
Both();
~Both();

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

#endif // KLASY_H
