#pragma once
#include "Projectile.h"

class AmmoList
{
public:
	AmmoList();

	void setTexture(std::string filename);

	bool pushBullet(const sf::Vector2f origin, const float direction);

	Projectile *& getHead() { return pHead; }
	void setHead(Projectile * newH) { pHead = newH; }

	int getBulletCount() const;
	void setBulletCount(const int newCount);

private:
	Projectile *pHead;
	int bulletCount = 0;
	std::string textureName;
};
