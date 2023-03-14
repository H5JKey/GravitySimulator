#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

class Object:sf::Drawable
{
public:
	float mass;
	sf::Vector2f pos;
	sf::Vector2f speed;
	sf::Vector2f boost, d_boost;
	std::string name;
	sf::CircleShape sprite;
	int radius;
	bool fixed;
	float color[3];


	Object(float mass, sf::Vector2f pos, sf::Vector2f speed=sf::Vector2f(0,0), std::string name="", sf::Color color=sf::Color(1,1,1), bool fixed=false, float radius=-1);

	Object();

	void UpdatePosition(float EllapsedTime);
	void UpdateSpeed(float EllapsedTime)

	void UpdateGraphic();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

	~Object() {}
};
