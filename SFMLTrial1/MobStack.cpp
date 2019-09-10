#include "MobStack.h"

Mob::Mob(float sps, int type, Difficulty d)
{
	pHead = nullptr;
	mDiff = d;
	spawnPerMinute = d.spawnPerMinute;
	mCount = 0;
	mMobType = type;
}

void Mob::update(sf::Clock c, Player &p, sf::Clock cooldown, sf::RenderWindow & window)
{
	//Spawns zombies
	if (((int)c.getElapsedTime().asMilliseconds()) % (int)(60000 / (spawnPerMinute)) == 0)
	{
		if (mCount < MAX_ZOMBIE_ON_SCREEN)
		{
			//std::cout << mCount << std::endl;
			spawnZombie();
		}
	}

	checkIfKilled(p, c, window);

}

void Mob::draw(sf::RenderWindow & window)
{
	Enemy *pCur = pHead;
	while (pCur != nullptr)
	{
		pCur->draw(window);
		pCur = pCur->getNext();
	}
}

void Mob::checkIfKilled(Player &p, sf::Clock c, sf::RenderWindow & window)
{
	Enemy *pCur = pHead, *temp = nullptr;
	while (pCur != nullptr)
	{
		if (((pCur)->isDead() && pCur->getAmmo().getBulletCount() == 0 && pCur->isFixed() == true) || pCur->getHasLeftScreen() || (pCur->getIsZombie() && pCur->isDead()))
		{
			mCount--;
			if (pCur == getHead())
			{
				setHead(getHead()->getNext());
			}

			if (pCur->getNext())
				pCur->getNext()->setPrev(pCur->getPrev());
			if (pCur->getPrev())
				pCur->getPrev()->setNext(pCur->getNext());

			temp = pCur;
			if (temp)
			{
				delete temp;
				pCur->setNext(nullptr);
			}

		}
		else if ((pCur)->update(p, c, window))
		{
			p.incScore(10);
		}

		pCur = pCur->getNext();
	}
}

void Mob::pushEnemy(const sf::Vector2f origin, const float speed)
{
	Enemy *pMem;

	//Randomly choose between three current enemy types
	int mobType = rand() % 3 + 1;
	switch (mobType)
	{
	case 3:
		pMem = new MGZombie(origin, speed, 2);
		break;
	case 2:
		pMem = new RZombie(origin, speed, 2);
		break;
	default:
		pMem = new Zombie(origin, speed, 2);
		break;
	}


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
	mCount++;
}

void Mob::spawnZombie()
{
	float randX = (float)(rand() % 1150 + 21);
	float randY = 0.0f;//rand() % 780 + 21;
	float randS = 0.0f;
	while ((randS < 0.03 || randS > 0.09) && randS < mDiff.speedCap)
		randS = (((float)rand()) / (float)RAND_MAX) * 0.3f;
	pushEnemy(sf::Vector2f(randX, randY), randS);
}