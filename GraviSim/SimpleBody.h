#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

class SimpleBody
{
public:
	int mass;
	sf::Vector2f pos;
	sf::Vector2f speed;
	sf::Vector2f boost;

	SimpleBody(int mass, sf::Vector2f pos, sf::Vector2f speed=sf::Vector2f(0,0));

	void Update(float EllapsedTime);

	sf::CircleShape GetDrawing();

	void UpdateBoost(SimpleBody& anotherBody);
};

