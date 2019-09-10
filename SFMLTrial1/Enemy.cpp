#include "Enemy.h"
Enemy::Enemy(sf::Vector2f loc, float s, int b)
{
	location = loc; speed = s; bps = b; pNext = pPrev = nullptr, attackSpeed = 1000;
}


void Enemy::draw(sf::RenderWindow & window)
{
	if (!isD)
		window.draw(sBody);
}

void Enemy::dealDamage(Player &player, sf::RenderWindow & window)
{
	player.reduceHealth(damage, window);
}

bool Enemy::update(Player &p, sf::Clock &c, sf::RenderWindow & window)
{
	bool killed = 0;
	float distance = 0.0f;
	float pDist = 0.0f;
	bool canDealDamage = false;
	Projectile *bCur = p.getAmmo().getHead();

	// check cool down
	if (c.getElapsedTime().asMilliseconds() % attackSpeed == 0)
	{
		canDealDamage = true;
	}
	//Attacks the player if within distance of 30
	if (getDistance(p.getLocation()) < ATTACK_RANGE)
	{
		//p.reduceHealth(damage);
		//int a = c.getElapsedTime().asMilliseconds();
		if (canDealDamage)
		{
			p.reduceHealth(damage, window);


		}

	}

	//Checks if hit by bullet
	while (bCur)
	{
		distance = getDistance(bCur->getLocation());
		if (distance < 20 && !isD)
		{
			isD = 1;
			killed = true;
		}
		bCur = bCur->getNext();
	}

	//Decrements score if the zombie leaves the bottom of the screen
	if (location.y > 800)
	{
		isD = 1;
		hasLeftScreen = true;
		p.decScore(10);
	}

	return killed;
}
AmmoList & Enemy::getAmmo(void)
{
	return ammo;
}
