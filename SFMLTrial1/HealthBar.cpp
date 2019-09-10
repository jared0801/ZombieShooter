#include "HealthBar.h"

HealthBar::HealthBar()
{
	// initiate sprites/textures
	tRedBar.loadFromFile("red_health_bar.png");
	sRedBar.setTexture(tRedBar);
	tGreenBar.loadFromFile("green_health_bar.png");
	sGreenBar.setTexture(tGreenBar);

	sRedBar.setOrigin(150, 12.5f);
	sGreenBar.setOrigin(145.5f, 7.5f);
	
	// set scale
	//sRedBar.setScale(.5, 1);
	//sGreenBar.setScale(.5, 1); 

	this->mPosition.x = 200;
	this->mPosition.y = 770;

	sGreenBar.setPosition(mPosition);
	sRedBar.setPosition(mPosition);

}

void HealthBar::updateHealthBar(float playerHealth, sf::RenderWindow & window)
{
	sGreenBar.setScale(playerHealth / 100, 1);
	window.draw(sRedBar);
	if (playerHealth < 0)
	{
		// do not draw
		playerHealth = 0;
	}
	else
	{
		window.draw(sGreenBar);
	}

}
