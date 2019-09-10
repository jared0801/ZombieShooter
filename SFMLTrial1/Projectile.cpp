#include "Projectile.h"

Projectile::Projectile(const sf::Vector2f origin, const float direction, std::string textureName)
{
	location.x = origin.x;
	location.y = origin.y;
	speed = 0.5f;
	tProj.loadFromFile(textureName);
	sProj.setTexture(tProj);
	sProj.setPosition(location.x, location.y);
	sProj.setOrigin(7.5f, 15.f);
	sProj.setRotation(direction);
	pNext = nullptr;
}

sf::Sprite &Projectile::getSprite()
{
	return sProj;
}
bool Projectile::update() {
	bool success = 1;

	//Delete this projectile if it goes off the screen
	if (location.y < 0 || location.y > 800 || location.x < 0 || location.x > 1200)
	{
		success = 0;
	}
	//move in direction of rotation
	else
	{
		location.x -= speed*cosf((PI*(sProj.getRotation() + 90)) / 180.f);
		location.y -= speed*sinf((PI*(sProj.getRotation() + 90)) / 180.f);
		sProj.setPosition(location);

	}

	return success;
}