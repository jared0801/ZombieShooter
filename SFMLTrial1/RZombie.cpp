#include "RZombie.h"

RZombie::RZombie(sf::Vector2f loc, float s, int b) : Enemy(loc, s, b)
{
	isZombie = 0;
	tBody.loadFromFile("RLZombie.png");
	ammo.setTexture("rocket.png");
	sBody.setTexture(tBody);
	isD = 0;
	sBody.setOrigin(15, 14);
}

//Returns true if killed
bool RZombie::update(Player &p, sf::Clock &c, sf::RenderWindow & window)
{
	float rotation = atan2(p.getLocation().y - sBody.getPosition().y, p.getLocation().x - sBody.getPosition().x);
	//Calls parent classes function
	bool killed;

	float distance = getDistance(p.getLocation());
	if (distance < DISTANCE && !isD)
	{
		sBody.setRotation((rotation * 180 / PI) + 270);
		//Shoot
		if (shootTimer.getElapsedTime().asMilliseconds() >  (SHOOT_SPEED*2))
		{
			shoot();
			shootTimer.restart();
		}
	}
	else
	{
		sBody.setRotation(0);
		location.y += speed;
	}


	sBody.setPosition(location);

	killed = Enemy::update(p, c, window);

	float damage = 10;
	float distance2;
	Projectile *bCur, *b = nullptr;
	bCur = ammo.getHead();
	while (bCur)
	{
		distance2 = p.getDistance(bCur->getLocation());
		if (distance2 < 20 && bCur->doneDamage == false)
		{
			p.reduceHealth(damage, window);
			bCur->doneDamage = true;

			if (bCur == ammo.getHead())
			{
				ammo.setHead(ammo.getHead()->getNext());
			}

			if (bCur->getNext())
				bCur->getNext()->setPrev(bCur->getPrev());
			if (bCur->getPrev())
				bCur->getPrev()->setNext(bCur->getNext());

			b = bCur;
			if (b)
			{
				delete b;
				bCur->setNext(nullptr);
			}
		}
		bCur = bCur->getNext();

	}


	return killed;
}

void RZombie::draw(sf::RenderWindow & window)
{
	drawBullets(window);
	Enemy::draw(window);
}

void RZombie::drawBullets(sf::RenderWindow & window)
{
	Projectile *bCur = ammo.getHead(), *b = nullptr;
	while (bCur)
	{

		//Draw each projectile to the window
		window.draw(bCur->getSprite());

		//Update each projectile and check if off screen
		if (!(bCur->update()))
		{
			//The projectile is off of the screen
			if (bCur == ammo.getHead())
			{
				ammo.setHead(ammo.getHead()->getNext());
			}

			if (bCur->getNext())
				bCur->getNext()->setPrev(bCur->getPrev());
			if (bCur->getPrev())
				bCur->getPrev()->setNext(bCur->getNext());

			b = bCur;

			if (b)
			{
				ammo.setBulletCount(ammo.getBulletCount() - 1);
				if (ammo.getBulletCount() == 0)
				{
					fix = true;
				}
				delete b;
				bCur->setNext(nullptr);
			}
		}

		bCur = bCur->getNext();
	}
}

void RZombie::shoot()
{
	ammo.pushBullet(location, sBody.getRotation() + 180);
}
