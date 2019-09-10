#pragma once
#include "Enemy.h"
#define DISTANCE 300
class RZombie : public Enemy
{
public:
	RZombie(sf::Vector2f loc, float s, int b);

	sf::Sprite &getSprite() { return sBody; }
	bool update(Player &p, sf::Clock &c, sf::RenderWindow & window);
	void draw(sf::RenderWindow & window);
	void drawBullets(sf::RenderWindow & window);
	void shoot();
	

private:
	sf::Clock shootTimer;
};