#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <ostream>
#include <istream>




class Object :sf::Drawable
{
private:
	sf::CircleShape m_picture;
public:
	float mass;                  //10^24 Kg						
	sf::Vector2f pos;			 //1 px - 10^3 km
	sf::Vector2f speed;			 //km/s
	sf::Vector2f acceleration;	 //km/s^2
	std::string name;
	sf::Color color;

	int radius;
	bool fixed;


	Object(float mass, int radius, sf::Vector2f pos, sf::Vector2f speed = sf::Vector2f(0, 0), std::string name = "", sf::Color color = sf::Color(255, 255, 255), bool fixed = false);
	Object();

	void updatePosition(float EllapsedTime);
	void updateSpeed(float EllapsedTime);
	void updateGraphic();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	bool collide(Object& anotherObject);
	bool collide(sf::Vector2f point);

	~Object() {}

};


