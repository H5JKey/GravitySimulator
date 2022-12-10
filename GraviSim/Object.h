#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

class Object
{
public:
	int mass;
	sf::Vector2f pos;
	sf::Vector2f speed;
	sf::Vector2f boost;
	std::string name;
	float color[3];


	Object(int mass, sf::Vector2f pos, sf::Vector2f speed=sf::Vector2f(0,0), std::string name="", sf::Color color=sf::Color(1,1,1));

	Object();

	void Update(float EllapsedTime);

	sf::CircleShape GetDrawing();

	void UpdateBoost(Object& anotherBody);
};

