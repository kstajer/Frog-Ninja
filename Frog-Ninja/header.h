#ifndef header_h
#define header_h

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

                            //global values responsible for:
extern float speed;		    //game speed
extern bool gamePause;	    //pausing game
extern bool gameOver;	    //ending game
extern bool gamePlay;	    //checking if player is in menu
extern bool gameControls;	//checking if player is in controls section
extern int score;			//score
extern bool restartGame;	//restart game

#define MAX_NUMBER_OF_ITEMS 3	//number of positions in menu

class Obstacle;

class Player {

	friend void collisionDetection(const Player*, const Obstacle*);

	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	float gravity = 1.2;
	int imageCount = 0;
	int row = 0;

public:

	float y = 800;
	float velocity = 0;

	Player();
	Player(std::string fileName);

	sf::Clock clockAnimation;	//clock used in animations
	void drawPlayer(sf::RenderWindow &window);
	void updateMovement();

};

class Background
{
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

public:
	float X = 0;
	Background();
	Background(std::string fileName);

	sf::Clock clock;
	void updateBackground(float &speed);
	void drawBackground(sf::RenderWindow &window);
};

class Scoreboard
{
	sf::Font font;
	sf::Text textScore;
	sf::Text gameOver;
	sf::Text yourScore;
	sf::Text playAgain;

public:
	sf::Text numbers;
	Scoreboard();
	Scoreboard(std::string fileName);

	void convertToString(int score);
	void drawScore(sf::RenderWindow &window);
	void drawGameOver(sf::RenderWindow &window);
};

class Obstacle
{
	sf::Texture obstacleTexture;
	sf::Clock clock;

	friend void collisionDetection(const Player*, const Obstacle*);
	friend void updateObstacle(Obstacle &obstacle1);
	friend void updateObstacle2(Obstacle &obstacle1);

public:
	float X=0;
	sf::Sprite obstacleSprite;

	Obstacle();
	Obstacle(std::string fileName);
	void drawObstacle(sf::RenderWindow &window);
};

class Menu
{
	sf::Texture menuTexture;	//main menu
	sf::Sprite menuSprite;

	sf::Texture controlsTexture;	//menu - controls section
	sf::Sprite controlsSprite;

public:
	int selectedItemIndex;	//chosen menu's text

	Menu(std::string fileName, std::string fileName2, float width, float height);
	//function drawing menu and controls section
	void draw(sf::RenderWindow &window);
	void drawControls(sf::RenderWindow &window);
	//function responsible for moving up and down
	void moveUp();
	void moveDown();

private:

	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

};

void collisionDetection(const Player* player, const Obstacle* obstacle);
void updateObstacle(Obstacle &obstacle1);
void updateObstacle2(Obstacle &obstacle1);
void playAgain(Player &player, Obstacle &obstacle1, Obstacle &obstacle2, Scoreboard &tab);

#endif //header_h
