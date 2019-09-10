#include "Zombie.h"
Zombie::Zombie(sf::Vector2f loc, float s, int b) : Enemy(loc, s, b)
{
	tBody.loadFromFile("Zombie.png");
	sBody.setTexture(tBody);
	isD = 0;
	sBody.setOrigin(16, 7);
	isZombie = true;
}

//Returns true if killed
bool Zombie::update(Player &p, sf::Clock &c, sf::RenderWindow & window)
{
	float rotation = atan2(p.getLocation().y - sBody.getPosition().y, p.getLocation().x - sBody.getPosition().x);
	//Calls parent classes function
	bool killed;

	float distance = getDistance(p.getLocation());
	if (distance < DISTANCE)
	{
		sBody.setRotation((rotation * 180 / PI) + 270);
	}
	else
	{
		sBody.setRotation(0);
	}
	if (this->getDistance(p.getLocation()) > 40)
	{
		location.y -= speed*sinf((PI*(sBody.getRotation() + 270)) / 180.f);
		location.x -= speed*cosf((PI*(sBody.getRotation() + 270)) / 180.f);
	}
	sBody.setPosition(location);
	
	killed = Enemy::update(p, c, window);

	return killed;

}
