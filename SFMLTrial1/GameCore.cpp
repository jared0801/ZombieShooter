#include "GameCore.h"

GameCore::GameCore()
{

}

void GameCore::runGame()
{
	srand((unsigned)time(NULL));
	sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML Window");
	char buffer[10];
	sf::String Score;
	sf::Text playerScore;

	sf::Texture tBackground;
	sf::Sprite sBackground;
	tBackground.loadFromFile("background.jpg");
	sBackground.setTexture(tBackground);

	sf::Clock shootTimer, spawnTimer1, cooldown;
	playerScore.setPosition(1130, 10);
	sf::Font font;
	font.loadFromFile("stocky.ttf");
	playerScore.setFont(font);
	playerScore.setCharacterSize(30);
	Difficulty d;
	char c;

	//Ask player to choose a difficulty
	std::cout << "What difficulty would you like to play on? (1 - Easy, 2 - Medium, 3 - Hard)\n";
	std::cin >> c;
	switch (c)
	{
	case '1':
		d.pShotPerSecond = 5;
		d.zShotPerSecond = 0;
		d.spawnPerMinute = 20;
		d.speedCap = 0.08f;
		break;
	case '2':
		d.pShotPerSecond = 3.5;
		d.zShotPerSecond = 0;
		d.spawnPerMinute = 50;
		d.speedCap = 0.1f;
		break;
	default:
	case '3':
		d.pShotPerSecond = 3;
		d.zShotPerSecond = 0;
		d.spawnPerMinute = 100;
		d.speedCap = 0.2f;
		break;
	}

	//Create player/mob according to difficulty
	Player p1(d);
	Mob m1(300, 1, d);

	//Create window
	while (window.isOpen())
	{
		Score = itoa(p1.getScore(), buffer, 10);
		playerScore.setString(Score);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}
		if (p1.isDead())
		{
			std::string in;
			int score = p1.getScore();
			while (in != "exit")
			{
				std::cout << "\nScore: " << score << std::endl;
				//hs.addScore(score);
				std::cout << "Type \"exit\" to quit." << std::endl;
				std::cin >> in;
			}
			window.close();
		}

		//Update
		p1.update(sf::Mouse::getPosition(window), shootTimer);
		m1.update(spawnTimer1, p1, cooldown, window);
		
		
		//Clear
		window.clear();

		//Draw
		window.draw(sBackground);
		m1.draw(window);
		p1.draw(window);
	
		window.draw(playerScore);
		_sleep(1);

		//Updates the window
		window.display();
	}
}