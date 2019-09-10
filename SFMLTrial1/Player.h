#pragma once
#include "AmmoList.h"
#include "HealthBar.h"
class Player
{
public:
	Player(Difficulty &d);

	void shoot();
	void move(sf::Vector2i mousePos);
	void lookLeft();
	void lookRight();

	void draw(sf::RenderWindow & window);
	void drawBullets(sf::RenderWindow & window);
	void update(sf::Vector2i mousePos, sf::Clock &c);

	AmmoList & getAmmo() { return ammo; }
	sf::Vector2f & getLocation() { return location; }

	void incScore(int add) {score += add; }
	void decScore(int sub) { score -= sub; }
	int getScore() const { return score; }

	void kill() { isD = 1; }
	bool isDead(){ return isD; }
	void reduceHealth(float &newHealth, sf::RenderWindow &window);

	float getDistance(sf::Vector2f loc2)
	{
		return sqrt((loc2.x - location.x) * (loc2.x - location.x) + (loc2.y - location.y) * (loc2.y - location.y));
	}
	
private:
	sf::Vector2f location;
	int score;
	bool isD = 0;
	//shots per second
	float bps;
	float speed, accel, deaccel, maxSpeed;
	sf::Texture tBody, tHead;
	sf::Sprite sBody, sHead;
	AmmoList ammo;
	float health;
	HealthBar healthbar;

};