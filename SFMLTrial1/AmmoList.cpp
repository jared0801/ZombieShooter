//A set/list of ammo
#include "AmmoList.h"

AmmoList::AmmoList()
{
	pHead = nullptr;
}

void AmmoList::setTexture(std::string filename)
{
	textureName = filename;
}

bool AmmoList::pushBullet(const sf::Vector2f origin, const float direction)
{
	this->bulletCount++;

	bool success = false;

	Projectile *pMem = new Projectile(origin, direction, textureName);
	if (!pHead)
	{
		pHead = pMem;
		pHead->setNext(nullptr);
		pHead->setPrev(nullptr);
		
	}
	else
	{
		pHead->setPrev(pMem);
		pMem->setNext(pHead);
		pMem->setPrev(nullptr);
		pHead = pMem;
	}

	return success;
}

int AmmoList::getBulletCount() const
{
	return bulletCount;
}

void AmmoList::setBulletCount(const int newCount)
{
	bulletCount = newCount;
}
