#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

class Object:sf::Drawable
{
public:
	float mass;
	sf::Vector2f pos;
	sf::Vector2f speed;
	sf::Vector2f acceleration;
	std::string name;
	sf::CircleShape sprite;
	int radius;
	bool fixed;
	float color[3];


	Object(float mass, sf::Vector2f pos, sf::Vector2f speed=sf::Vector2f(0,0), std::string name="", sf::Color color=sf::Color(1,1,1), bool fixed=false, float radius=-1);

	Object();

	void updatePosition(float EllapsedTime);
	void updateSpeed(float EllapsedTime);

	void updateGraphic();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

	~Object() {}
};

