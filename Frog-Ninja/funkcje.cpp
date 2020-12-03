#include "header.h"

float speed = 12;
bool gamePause = false;
bool gameOver = false;
bool gamePlay = false;
bool gameControls = false;
bool restartGame = false;
int score = -2;

Player::Player(std::string fileName)
{
	if (!playerTexture.loadFromFile(fileName))		//loading player texture
		std::cerr << "Error";
	playerSprite.setOrigin(0, 96);
	playerSprite.setPosition(200, 800);			//set starting position
}

void Player::drawPlayer(sf::RenderWindow &window)
{
	sf::Time switchTime = clockAnimation.getElapsedTime();

	if (y == 800) row = 0;                         // run animation
	else row = 1;                                // jump animation

	if (switchTime.asSeconds() > 0.05f)             // 0.1s = animation frame switch time
	{
		if (imageCount == 11)                    // amount of frames for one animation -1
			imageCount = 0;
		else
			imageCount++;
		clockAnimation.restart();
	}
	if (row == 1) imageCount = 0;
	sf::IntRect rectSourceSprite(imageCount * 96, row * 96, 96, 96);   // one frame (96x96)
	sf::Sprite playerSprite(playerTexture, rectSourceSprite);

	playerSprite.setTextureRect(rectSourceSprite);
	playerSprite.setOrigin(0, 96);
	playerSprite.setPosition(200, y);           // updates player position

	window.draw(playerSprite);

}

//updates player position during jumps
void Player::updateMovement()
{
	y += velocity;

	if (y < 800) velocity += gravity;
	else if (y > 800) y = 800;

	playerSprite.setPosition(200, y);
}


Background::Background(std::string fileName)
{
	if (!backgroundTexture.loadFromFile(fileName))		//loads background texture
		std::cerr << "Error";


	//background properties
	backgroundTexture.setRepeated(true);
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0, 0);
	backgroundSprite.setTextureRect(sf::IntRect(X, 0, 2200, 1200));
}

//moving and accelerating
void Background::updateBackground(float &speed)
{

	if (X < 2200) X += speed;
	else X = 0;
	backgroundSprite.setTextureRect(sf::IntRect(X, 0, 2200, 1200));

	sf::Time ileMinelo = clock.getElapsedTime();
	if (ileMinelo.asSeconds() > 3)
	{
		if (speed < 30) speed += 0.5;			
		clock.restart();
	}

}

//displaying background
void Background::drawBackground(sf::RenderWindow &window)
{
	window.draw(backgroundSprite);
}


Scoreboard::Scoreboard(std::string fileName)
{
	if (!font.loadFromFile(fileName))
	{
		std::cerr << "Error";
	}

	//fonts, texts
	textScore.setFont(font);
	textScore.setString("Score: ");
	textScore.setFillColor(sf::Color::Black);
	textScore.setCharacterSize(60);
	textScore.setPosition(960, 20);

	numbers.setFont(font);
	numbers.setString("0");
	numbers.setFillColor(sf::Color::Black);
	numbers.setCharacterSize(60);
	numbers.setPosition(1190, 20);

	gameOver.setFont(font);
	gameOver.setString("GAME OVER");
	gameOver.setFillColor(sf::Color::Black);
	gameOver.setCharacterSize(180);
	gameOver.setPosition(560, 200);

	yourScore.setFont(font);
	yourScore.setString("Your score: ");
	yourScore.setFillColor(sf::Color::Black);
	yourScore.setCharacterSize(80);
	yourScore.setPosition(750, 440);

	playAgain.setFont(font);
	playAgain.setString("Press 'R' to play again");
	playAgain.setFillColor(sf::Color::Black);
	playAgain.setCharacterSize(60);
	playAgain.setPosition(680, 560);
}

//converts score from int to string
void Scoreboard::convertToString(int score)
{
	std::stringstream s;
	s << score;
	numbers.setString(s.str());
}

//displays current score
void Scoreboard::drawScore(sf::RenderWindow &window)
{
	window.draw(textScore);
	window.draw(numbers);
}

//displays game over screen
void Scoreboard::drawGameOver(sf::RenderWindow &window)
{
	window.draw(gameOver);
	window.draw(yourScore);
	numbers.setCharacterSize(80);
	numbers.setPosition(1350, 440);
	numbers.setFillColor(sf::Color::Red);
	window.draw(numbers);
	window.draw(playAgain);
}


Obstacle::Obstacle(std::string fileName)
{
	if (!obstacleTexture.loadFromFile(fileName))		//loads obstacle texture
		std::cerr << "Error";

	//obstacle properties
	obstacleSprite.setTexture(obstacleTexture);
	obstacleSprite.setOrigin(80, 80);
	obstacleSprite.setPosition(2200, 820);
}

//displays obstacle
void Obstacle::drawObstacle(sf::RenderWindow &window)
{
	window.draw(obstacleSprite);
}


//detects collision
void collisionDetection(const Player* player, const Obstacle* obstacle)
{
	sf::FloatRect playerShape = player->playerSprite.getGlobalBounds();
	sf::FloatRect obstacleShape = obstacle->obstacleSprite.getGlobalBounds();

	playerShape.width = 96;                 // player width
	playerShape.height = 96;                // player height

	//ends game while collision is detected
	if (playerShape.intersects(obstacleShape))	
	{
		gamePause = true;
		gameOver = true;
	}
}

//updates obstacle position
void updateObstacle(Obstacle &obstacle1)
{
	sf::Clock clock;
	if (obstacle1.X > 0) obstacle1.X = obstacle1.X - speed;
	else
	{
		obstacle1.X = 2200;
		score++;
	}

	(obstacle1.obstacleSprite).setPosition(obstacle1.X, 820);

}

void updateObstacle2(Obstacle &obstacle1)
{
	sf::Clock clock;
	if (obstacle1.X > 0) obstacle1.X = obstacle1.X - speed;
	else
	{
		obstacle1.X = 3300;
		score++;
	}

	(obstacle1.obstacleSprite).setPosition(obstacle1.X, 820);
}

//restarts game
void playAgain(Player &player, Obstacle &obstacle, Obstacle &obstacle2, Scoreboard &tab)
{
	speed = 8;
	score = 0;
	gamePause = false;
	gameOver = false;
	player.y = 800;
	obstacle1.X = 2200;
	obstacle2.X = 3300;
	tab.numbers.setCharacterSize(60);
	tab.numbers.setPosition(1190, 20);
	tab.numbers.setFillColor(sf::Color::Black);
};


Menu::Menu(std::string fileName, std::string fileName2, float width, float height)
{
	if (!font.loadFromFile("resources/pixel.ttf"))
		std::cerr << "Error";
	if (!menuTexture.loadFromFile(fileName))
		std::cerr << "Error";
	if (!controlsTexture.loadFromFile(fileName2))
		std::cerr << "Error";

	menuSprite.setTexture(menuTexture);
	menuSprite.setPosition(0, 0);

	controlsSprite.setTexture(controlsTexture);
	controlsSprite.setPosition(0, 0);
	//PLAY
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setCharacterSize(100);
	menu[0].setString("Play");
	menu[0].setPosition(200, height / 6 + 300);
	//CONTROLS
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setCharacterSize(100);
	menu[1].setString("Controls");
	menu[1].setPosition(200, height / 6 * 2 + 300);
	//EXIT
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setCharacterSize(100);
	menu[2].setString("Exit");
	menu[2].setPosition(200, height / 6 * 3 + 300);

	selectedItemIndex = 0;
}

void Menu::draw(sf::RenderWindow &window)
{
	window.draw(menuSprite);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)	//drawing menu texts
	{
		window.draw(menu[i]);
	}
}
void Menu::drawControls(sf::RenderWindow &window)
{
	window.draw(controlsSprite);
}
//moving with arrow keys
//selected option change color to red and slightly increase font size
void Menu::moveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		menu[selectedItemIndex].setCharacterSize(100);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
		menu[selectedItemIndex].setCharacterSize(110);
	}
}
void Menu::moveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		menu[selectedItemIndex].setCharacterSize(100);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
		menu[selectedItemIndex].setCharacterSize(110);
	}
}
