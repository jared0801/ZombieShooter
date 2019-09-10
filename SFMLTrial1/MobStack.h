#pragma once
#include "Zombie.h"
#include "MGZombie.h"
#include "RZombie.h"
#include <vector>
#include <iostream>

//Mob types: 1) Zombie
//			2) MG Zombie
//			3) Rocket Zombie

class Mob
{
public:
	Mob(float sps, int type, Difficulty d);
	void update(sf::Clock c, Player &p, sf::Clock cooldown, sf::RenderWindow & window);
	void draw(sf::RenderWindow & window);

	
	Enemy *& getHead() { return pHead; }
	void setHead(Enemy * newH) { pHead = newH; }

private:
	void checkIfKilled(Player &p, sf::Clock c, sf::RenderWindow & window);
	void pushEnemy(const sf::Vector2f origin, const float speed);
	void spawnZombie();

	float spawnPerMinute;
	Enemy *pHead;
	int mCount, mMobType;
	Difficulty mDiff;
};