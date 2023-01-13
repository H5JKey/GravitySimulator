#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

class Object:sf::Drawable
{
public:
	int mass;
	sf::Vector2f pos;
	sf::Vector2f speed;
	sf::Vector2f boost;
	std::string name;
	sf::CircleShape sprite;
	bool fixed;
	float color[3];


	Object(int mass, sf::Vector2f pos, sf::Vector2f speed=sf::Vector2f(0,0), std::string name="", sf::Color color=sf::Color(1,1,1), bool fixed=false);

	Object();

	void UpdateParams(float EllapsedTime);

	void UpdateGraphic();


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;


	void UpdateBoost(Object& anotherBody);
};

