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

	void Update(float EllapsedTime, SimpleBody& anotherBody);

	sf::CircleShape GetDrawing() {
		sf::CircleShape c(30);
		c.setPosition(pos);
		return c;

	}
};

