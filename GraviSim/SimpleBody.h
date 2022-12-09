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
	std::string name;

	SimpleBody(int mass, sf::Vector2f pos, sf::Vector2f speed=sf::Vector2f(0,0), std::string name="NoName");

	SimpleBody();

	void Update(float EllapsedTime);

	sf::CircleShape GetDrawing();

	void UpdateBoost(SimpleBody& anotherBody);
};

