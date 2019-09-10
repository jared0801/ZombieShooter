#pragma once
#include "AmmoList.h"
#include "Player.h"
#include <iostream>
#define ATTACK_RANGE 45
#define SHOOT_SPEED 500
#define MAX_ZOMBIE_ON_SCREEN 20
class Enemy 
{
public:
	Enemy(sf::Vector2f loc, float s, int b);


	virtual void draw(sf::RenderWindow & window);
	void dealDamage(Player &player, sf::RenderWindow & window);
	virtual bool update(Player &p, sf::Clock &c, sf::RenderWindow & window);

	//Stack node functions
	Enemy * getNext() { return pNext; }
	void setNext(Enemy *next) { pNext = next; }
	Enemy * getPrev() { return pPrev; }
	void setPrev(Enemy *prev) { pPrev = prev; }

	//Finds the distance between this enemy and some other vector2f
	float Enemy::getDistance(sf::Vector2f loc2)
	{
		return sqrt((loc2.x - location.x) * (loc2.x - location.x) + (loc2.y - location.y) * (loc2.y - location.y));
	}

	bool isDead() { return isD; }

	AmmoList & getAmmo(void);
	bool &isFixed() { return fix; }
	bool &getHasLeftScreen() { return hasLeftScreen; }
	bool &getIsZombie() { return isZombie; }

protected:
	Enemy *pNext, *pPrev;
	sf::Vector2f location;
	int bps;
	bool isD;
	float speed;
	sf::Texture tBody;
	sf::Sprite sBody;
	float damage = 5;
	bool fix = false;
	bool hasLeftScreen = false;
	bool isZombie;
	unsigned int attackSpeed;
	AmmoList ammo;
};