#pragma once
#define DISTANCE 300
#include "Enemy.h"

class MGZombie : public Enemy
{
public:
	MGZombie(sf::Vector2f loc, float s, int b);

	sf::Sprite &getSprite() { return sBody; }
	bool update(Player &p, sf::Clock &c, sf::RenderWindow & window);
	void draw(sf::RenderWindow & window);
private:
	void shoot(void);
	void drawBullets(sf::RenderWindow & window);
	sf::Clock shootTimer;


};