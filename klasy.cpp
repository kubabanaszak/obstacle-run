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

Player::Player() {};
Player::~Player() {};

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
