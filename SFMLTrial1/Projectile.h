#pragma once
#define PI 3.1415f
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

typedef struct
{
	float pShotPerSecond;
	float zShotPerSecond;
	float spawnPerMinute;
	float speedCap;

}Difficulty;

class Projectile
{
public:
	Projectile(const sf::Vector2f origin, const float direction, std::string textureName);

	sf::Sprite &getSprite();
	bool update();
	Projectile * getNext() { return pNext; }
	void setNext(Projectile *next) { pNext = next; }
	Projectile * getPrev() { return pPrev; }
	void setPrev(Projectile *prev) { pPrev = prev; }
	sf::Vector2f getLocation() const { return location; }
	float getDistance(sf::Vector2f loc2)
	{
		return sqrt((loc2.x - location.x) * (loc2.x - location.x) + (loc2.y - location.y) * (loc2.y - location.y));
	}

	bool doneDamage = false;
private:
	sf::Vector2f location;
	float speed;
	Projectile *pNext, *pPrev;
	sf::Texture tProj;
	sf::Sprite sProj;
	//bool player;
};
