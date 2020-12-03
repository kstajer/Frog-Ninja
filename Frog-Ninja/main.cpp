#include "header.h"

int main() {

	srand(time(NULL));

	//creating class objects
	Player gracz1("resources/zabaFrames.png");	
	Obstacle przeszkoda1("resources/przeszkoda.png");
	Obstacle przeszkoda2("resources/przeszkoda2.png");
	Background sky("resources/sky.png");
	Background ground("resources/ground.png");
	Scoreboard tablica("resources/pixel.ttf");
	Menu menu("resources/menuBackground.png", "resources/menuControls.png", 2200, 1200);	//menu textures

	sf::RenderWindow window(sf::VideoMode(2200, 1200), "Frog Ninja");   //creating window
	window.setFramerateLimit(60);

	sf::Clock clock;		

	//music
	sf::Music music;
	if (!music.openFromFile("resources/muzyczka.ogg"))
		std::cerr << "Error";
	music.setVolume(15);
	music.setLoop(true);

	//jump sound
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("resources/skok.wav"))
	sf::Sound skok;
	sf::Sound cos;
	cos.setBuffer(buffer);

	music.play();

	//main game loop
	while (window.isOpen())    
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			//jump
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && gracz1.y >= 770)
			{
				gracz1.velocity = -20;
				cos.play();
			}

			//pause
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P && gamePause == false)
			{
				gamePause = true;
				music.stop();
			}
			//resume
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P && gamePause == true && gameOver == false)

			{
				gamePause = false;
				music.play();
			}
			//restart
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R && gameOver == true)
			{
				restartGame = true;
				gamePause = false;
			}
			if (!gamePlay)	//moving in menu
			{
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
				{
					menu.moveUp();
				}
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
				{
					menu.moveDown();
				}
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
				{
					switch (menu.selectedItemIndex)
					{
					case 0:
						gamePlay = true;
						break;
					case 1:
						gameControls = true;
						break;
					case 2:
						window.close();
						break;
					}
				}
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B)
				{
					gameControls = false;
				}
			}
		}

		//game logic
		if (gamePlay && !gameControls)
		{
			if (!gamePause)
			{
				gracz1.updateMovement();
				updateObstacle(przeszkoda1);
				updateObstacle2(przeszkoda2);
				sky.updateBackground(speed);
				ground.updateBackground(speed);
				collisionDetection(&gracz1, &przeszkoda1);
				collisionDetection(&gracz1, &przeszkoda2);
				tablica.convertToString(score);
			}

			//display game
			window.clear();

			sky.drawBackground(window);
			ground.drawBackground(window);
			gracz1.drawPlayer(window);
			przeszkoda1.drawObstacle(window);
			przeszkoda2.drawObstacle(window);
			if (!gameOver)tablica.drawScore(window);
			if (gameOver)
			{
				tablica.drawGameOver(window);
			}
			if (restartGame)
			{
				playAgain(gracz1, przeszkoda1, przeszkoda2, tablica);
				restartGame = false;
			}
			window.display();
		}
		else if (!gamePlay && !gameControls)
		{
			window.clear();
			menu.draw(window);
			window.display();
		}
		else if (!gamePlay && gameControls)
		{
			window.clear();
			menu.drawControls(window);
			window.display();
		}
	}

	return 0;
}
