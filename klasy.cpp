#include "klasy.h"

Player::Player() 
{
    shape.setSize(sf::Vector2f(100, 100));
    t[0].loadFromFile("run_1.png");
    t[1].loadFromFile("run_2.png");
    t[2].loadFromFile("jump.png");
    t[3].loadFromFile("slide.png");
    t[4].loadFromFile("emoji.png");
    shape.setTexture(&t[0]);
}

Player::~Player() {}

void Player::setPosition(float x, float y) {shape.setPosition(x, y); }

sf::Vector2f Player::getPosition() {return shape.getPosition(); }

sf::RectangleShape& Player::getShape() {return shape; }

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
    if (textureClock.getElapsedTime().asSeconds() >= switchTime) 
    {
        if (useFirstTexture) 
        {
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

void Player::endTexture() {shape.setTexture(&t[4]); }

void Player::draw(sf::RenderWindow& window) { window.draw(shape); }

void Player::setID(int id) { ID = id; }

int Player::getID() { return ID; }

std::ostream& operator<<(std::ostream& os, const Player& player)
{
    os << player.ID << " " << player.name << " " << player.results << "\n";
    return os;
}

Text::Text(float s, float x, float y)
{
    size = s;
    font.loadFromFile("arial.ttf");
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::White);
    text.setPosition(x, y);
}

Text::Text(float s, float x, float y, std::string disp)
{
    size = s;
    font.loadFromFile("arial.ttf");
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::White);
    text.setPosition(x, y);
    text.setString(disp);
}

Text::~Text() {}

void Text::draw(sf::RenderWindow& window) { window.draw(text); }

void Text::setString (const std::string& str) { text.setString(str); }

void Text::SetFillColor(const sf::Color& color) { text.setFillColor(color); }

sf::FloatRect Text::getGlobalBounds() const { return text.getGlobalBounds(); }

void Text::setPosition(float x, float y) { text.setPosition(x, y); }

HighScores::HighScores() 
{
    std::ifstream file("results.txt");
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: results.txt" << std::endl;
        return;
    }
    std::string line;
    int y = 250; 
    while (std::getline(file, line)) 
    {
        std::stringstream ss(line);
        int score;
        if (ss >> score) 
        {
            std::string display = "Score: " + std::to_string(score);
            Text* text = new Text(30, 200, y, display);
            scores.push_back(text);
            y += 100; 
        }
    }
}

HighScores::~HighScores() 
{
    for (auto t : scores) delete t;
}

void HighScores::draw(sf::RenderWindow& window) 
{
    for (auto t : scores) 
    {
        t->draw(window);
    }
}

Menu::Menu() 
{
    item[0] = new Text(30, 225, 400, "Start game");
    item[1] = new Text(30, 225, 500, "Highscores");
    item[2] = new Text(30, 265, 600, "Exit");
    item[3] = new Text(30, 2000, 2000, "Back");
    title = new Text(60, 125, 100, "Obstacle run");
    EnterName = new Text(30, 2000, 2000, "Enter your name:");
    playerText = new Text(24, 2000, 2000, " ");
    playerText->SetFillColor(sf::Color::Black);
    highScores = new HighScores();
    inputBox.setSize(sf::Vector2f(300, 50));
    inputBox.setPosition(2000, 2000);
    inputBox.setFillColor(sf::Color::White);
}

Menu::~Menu() 
{
    for (int i = 0; i < 4; i++) delete item[i];
    delete title;
    delete EnterName;
    delete playerText;
    delete highScores;
}

void Menu::draw(sf::RenderWindow& window)
{
    if (showHighScores) 
    {
        item[3]->setPosition(260, 525);
        highScores->draw(window);
        item[2]->draw(window);
        item[3]->draw(window);
        return;
    }
    title->draw(window);
    EnterName->draw(window);
    for (int i = 0; i < 3; i++) item[i]->draw(window);
    drawBox(window);
    playerText->draw(window);
}

void Menu::drawBox(sf::RenderWindow& window) 
{
    window.draw(inputBox);
}

MenuEvent Menu::processEvent(sf::RenderWindow& window, sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (item[0]->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            return MenuEvent::StartGameClicked;

        if (item[1]->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            return MenuEvent::HighScoresClicked;

        if (item[2]->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            return MenuEvent::ExitClicked;

        if (item[3]->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            return MenuEvent::BackClicked;
    }
    if (buttonClicked)
    {
        item[0]->setPosition(2000, 2000);
        item[1]->setPosition(2000, 2000);
        title->setPosition(2000, 2000);
        EnterName->setPosition(185, 275);
        playerText->setPosition(155, 360);
        inputBox.setPosition(150, 350);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            if (!playerName.empty())
                return MenuEvent::NameEntered;
        }
    }
    if (event.type == sf::Event::TextEntered && buttonClicked)
    {
        if (event.text.unicode < 128)
        {
            if (event.text.unicode == '\b' && !playerName.empty())
                playerName.pop_back();
            else if (event.text.unicode != '\b')
                playerName += static_cast<char>(event.text.unicode);
            playerText->setString(playerName);
        }
    }
    return MenuEvent::None;
}

bool Menu::isButtonClicked() { return buttonClicked; }

std::string Menu::getPlayerName() { return playerName; }

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

Obstacle::Obstacle(float width, float height, const std::string& textureFile) : width(width), height(height), textureFile(textureFile)
{
    shape.setSize(sf::Vector2f(width, height));
    texture.loadFromFile(textureFile);
    shape.setTexture(&texture);
}

Obstacle::~Obstacle() {};

void Obstacle::setPosition(float x, float y) { shape.setPosition(x, y); }

sf::Vector2f Obstacle::getPosition() { return shape.getPosition(); }

void Obstacle::draw(sf::RenderWindow& window) { window.draw(shape); }

Up::Up() : Obstacle(100, 100, "obstacle_up.png") {};

Up::~Up() {};

bool Up::checkCollision(Player& player)
{
    if (shape.getGlobalBounds().intersects(player.getShape().getGlobalBounds()))
    {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            return true;
    }
    return false;
}

Down::Down() : Obstacle(100, 150, "obstacle_down.png") {};

Down::~Down() {};

bool Down::checkCollision(Player& player)
{
    if (shape.getGlobalBounds().intersects(player.getShape().getGlobalBounds()))
    {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            return true;
    }
    return false;
}

Both::Both() : Obstacle(100, 100, "obstacle.png") {};

Both::~Both() {};

bool Both::checkCollision(Player& player)
{
    if (shape.getGlobalBounds().intersects(player.getShape().getGlobalBounds()))
    {
        if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
            return true;
    }
    return false;
}

Game::Game(float width, float height, std::string GameName)
    : width(width), height(height), GameName(GameName),
    gameOver(false), moveLeft(false), moveRight(false),
    gameStarted(false), gameOverText(50, 150, 400, "GAME OVER"),
    exitText(40, 260, 750, "EXIT")
    {
    window.create(sf::VideoMode(width, height), GameName, sf::Style::Close);
    player.setPosition(250, 600);
    backgroundTexture.loadFromFile("background.png");
    background.setTexture(backgroundTexture);
    }

Game::~Game() 
{
    for (auto& pair : obstacles) delete pair.first;
}

void Game::run() 
{
    while (window.isOpen()) 
    {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() 
{
    sf::Event event;
    while (window.pollEvent(event)) 
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (!gameStarted)
        {
            MenuEvent menuEvent = menu.processEvent(window, event);
            switch (menuEvent) {
            case MenuEvent::StartGameClicked:
                menu.buttonClicked = true;
                break;
            case MenuEvent::HighScoresClicked:
                menu.showHighScores = true;
                break;
            case MenuEvent::ExitClicked:
                window.close();
                break;
            case MenuEvent::BackClicked:
                menu.showHighScores = false;
                break;
            case MenuEvent::NameEntered:
                gameStarted = true;
                break;
            default:
                break;
            }
        }
        else if (gameOver)
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (exitText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    window.close();
                }
            }
        }
    }
}

void Game::update() 
{
    if (!gameStarted) 
    {
        scoreClock.restart();
        return;
    }
    if (!gameOver) 
    {
        movement();
        score.Showscore(scoreClock);
        los();
        for (auto& pair : obstacles) 
        {
            if (pair.first->checkCollision(player)) 
            {
                gameOver = true;
                break;
            }
        }
    }
}

void Game::render() 
{
    window.clear();
    if (!gameStarted) 
    {
        menu.draw(window);
    }
    else {
        window.draw(background);
        for (auto& pair : obstacles)
            pair.first->draw(window);
        score.draw(window);
        player.draw(window);
        player.textureChange();
        if (gameOver) 
        {
            player.endTexture();
            gameOverText.draw(window);
            score.result = score.getScore();
            exitText.draw(window);
        }
    }
    window.display();
}

void Game::movement() 
{
    sf::Vector2f pos = player.getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        player.setPosition(pos.x, 550);
    else
        player.setPosition(pos.x, 600);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !moveLeft) 
    {
        if (pos.x == 250) player.setPosition(50, pos.y);
        else if (pos.x == 450) player.setPosition(250, pos.y);
        moveLeft = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !moveRight) 
    {
        if (pos.x == 250) player.setPosition(450, pos.y);
        else if (pos.x == 50) player.setPosition(250, pos.y);
        moveRight = true;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A)) moveLeft = false;
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D)) moveRight = false;
}

void Game::los()
{
    float spawnInterval = 0.7;
    float obstacleLifespan = 9;
    float moveSpeed = 0.3;
    if (clock.getElapsedTime().asSeconds() >= spawnInterval)
    {
        int lane = rand() % 3;
        int type = rand() % 3;
        float x = (lane == 0) ? 50 : (lane == 1) ? 250 : 450;
        Obstacle* newObstacle = nullptr;
        if (type == 0) newObstacle = new Up();
        else if (type == 1) newObstacle = new Down();
        else newObstacle = new Both();
        if (newObstacle) 
        {
            newObstacle->setPosition(x, -200);
            obstacles.push_back( {newObstacle, sf::Clock()} );
        }
        clock.restart();
    }

    for (auto it = obstacles.begin(); it != obstacles.end();)
    {
        float moveAmount = moveSpeed * it->second.getElapsedTime().asSeconds();
        sf::Vector2f currentPos = it->first->getPosition();
        it->first->setPosition(currentPos.x, currentPos.y + moveAmount);
        if (it->second.getElapsedTime().asSeconds() >= obstacleLifespan)
        {
            delete it->first;
            it = obstacles.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Game::generateID() 
{
    std::ifstream file("base.txt");
    if (!file.is_open()) 
    {
        std::cerr << "failed to open file: base.txt" << std::endl;
        currentID = 1;
        return;
    }
    std::string lastLine;
    std::string line;
    while (std::getline(file, line)) 
    {
        if (!line.empty())
            lastLine = line;
    }
    file.close();
    if (lastLine.empty()) 
    {
        currentID = 1;
        return;
    }
    std::istringstream iss(lastLine);
    int lastID;
    if (iss >> lastID) 
    {
        currentID = lastID + 1;
    }
    else 
    {
        currentID = 1; 
    }
}

void Game::getData() 
{
    player.setID(currentID);
    player.name = menu.getPlayerName();
    player.results = score.result;
}

void Game::savePlayerData() 
{
    if (!gameStarted || !gameOver) return;
    std::fstream file("base.txt", std::ios::app);
    if (!file.is_open()) 
    {
        std::cerr << "failed to open file: base.txt" << std::endl;
        return;
    }
    else
    {
        file << player;
        file.close();
    }
}

void Game::loadScores() 
{
    std::fstream file("results.txt", std::ios::in);
    if (file.is_open()) 
    {
        std::string line;
        while (getline(file, line))
        {
            double d_line = std::stod(line);
            topScores.emplace_back(d_line);
        }
        file.close();
    }
    else 
    {
        for (int i = 0; i < 3; i++)
        {
            std::cerr << "failed to open file: results.txt" << std::endl;
            topScores.emplace_back(0);
        }
    }
}

void Game::sortScores()
{
    topScores.emplace_back(player.results);
    std::sort(topScores.begin(), topScores.end());
}

void Game::saveScores() 
{
    if (!gameStarted || !gameOver) return;
    std::fstream file("results.txt", std::ios::out);
    if (!file.is_open()) 
    {
        std::cerr << "failed to open file: results.txt" << std::endl;
        return;
    }
    else
    {
        for (int i = 3; i > 0; i--) 
        {
            file << topScores[i] << "\n";
        }
        file.close();
    }
}
