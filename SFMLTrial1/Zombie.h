#pragma once
#include "Enemy.h"
#define DISTANCE 300

class Zombie : public Enemy
{
public:
	Zombie(sf::Vector2f loc, float s, int b);

	sf::Sprite &getSprite() { return sBody; }
	bool update(Player &p, sf::Clock &c, sf::RenderWindow & window);
private:



};