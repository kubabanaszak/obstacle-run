#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "klasy.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <fstream>

int main()
{
    Game game(600, 900, "Obstacle run");
    game.generateID();
    game.loadScores();
    game.run();
    game.getData();
    game.savePlayerData();
    game.sortScores();
    game.saveScores();
    return 0;
}


