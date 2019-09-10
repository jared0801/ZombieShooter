#include "Player.h"

Player::Player(Difficulty &d)
{
	//Spawn location
	location.x = 375;
	location.y = 520;

	//Variable initialization
	score = 0;
	speed = 0.0f;
	bps = d.pShotPerSecond;
	maxSpeed = 0.2f;
	accel = 0.01f;
	deaccel = 0.002f;
	health = 100;

	ammo.setTexture("bullet.png");

	tBody.loadFromFile("RedTankBody.png");
	tHead.loadFromFile("TankTop.png");

	sBody.setTexture(tBody);
	sHead.setTexture(tHead);
	sBody.setPosition(location.x, location.y);
	sBody.setOrigin(23, 20);

	sHead.setPosition(location.x, location.y);
	sHead.setOrigin(12, 26);
	
}

//
void Player::move(sf::Vector2i mousePos)
{
	//Rotates the head to follow the mouse
	float hRotation = atan2(mousePos.y - sHead.getPosition().y, mousePos.x - sHead.getPosition().x);

	//Wraps around screen
	if (location.y < 0)
	{
		location.y = 800;
	}
	else if (location.y > 800)
	{
		location.y = 0;
	}
	else if (location.x < 0)
	{
		location.x = 1200;
	}
	else if (location.x > 1200)
	{
		location.x = 0;
	}

	//Rotates body if A or D keys are pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		lookLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		lookRight();

	//Accelerates in direction of body
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (speed < maxSpeed)
			speed += accel;
		else if (speed > 0)
			speed -= deaccel;
	}
	//deaccelerates/reverses in opposite direction of body
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (speed > -maxSpeed)
			speed -= accel;
		else if (speed < 0)
			speed += deaccel;
	}
	//Deaccelerate from friction
	else
	{
		if (speed > 0)
			speed -= deaccel;
		else if (speed < 0)
			speed += deaccel;
	}

	//Translates player according to events above
	location.y -= speed*sinf((PI*(sBody.getRotation() + 90)) / 180.f);
	location.x -= speed*cosf((PI*(sBody.getRotation() + 90)) / 180.f);

	sBody.setPosition(location.x, location.y);
	sHead.setRotation(90+(hRotation*180 / PI));
	sHead.setPosition(location.x, location.y);
}

void Player::shoot()
{
	ammo.pushBullet(getLocation(), sHead.getRotation());
}

void Player::lookLeft()
{
	sBody.rotate(-0.3f);
}

void Player::lookRight()
{
	sBody.rotate(0.3f);
}

void Player::draw(sf::RenderWindow & window)
{
	healthbar.updateHealthBar(health, window);
	if (!isD)
	{
		window.draw(sBody);
		window.draw(sHead);

		drawBullets(window);
	}

}

void Player::drawBullets(sf::RenderWindow & window)
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
				delete b;
				bCur->setNext(nullptr);
			}
		}

		bCur = bCur->getNext();
	}
}

void Player::update(sf::Vector2i mousePos, sf::Clock &clock)
{
	bool hurt = false;
	move(mousePos);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (clock.getElapsedTime().asMilliseconds() > 1000/bps)
		{
			shoot();
			clock.restart();
		}
	}
	if (health == 0)
	{
		isD = true;
	}
}



void Player::reduceHealth(float & newHealth, sf::RenderWindow & window)
{
	health -= newHealth;
	this->healthbar.updateHealthBar(health, window);

}
