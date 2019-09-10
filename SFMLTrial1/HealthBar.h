#include <SFML/Graphics.hpp>

class HealthBar
{
public:
	HealthBar();
	void updateHealthBar(float playerHealth, sf::RenderWindow & window);
private:
	sf::Sprite sRedBar;
	sf::Sprite sGreenBar;
	sf::Texture tRedBar;
	sf::Texture tGreenBar;
	sf::Vector2f mPosition;

};