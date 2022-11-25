#include "SimpleBody.h"
#include <iostream>


SimpleBody::SimpleBody(int mass, sf::Vector2f pos, sf::Vector2f speed) {
	this->pos = pos;
	this->mass = mass;//Â 10^12 êã
	this->speed = speed;
}

void SimpleBody::Update(float EllapsedTime) {

	this->pos += this->speed * EllapsedTime + (this->boost * EllapsedTime * (EllapsedTime/2));
	this->speed += this->boost * EllapsedTime;
	this->boost = sf::Vector2f(0,0);
}

sf::CircleShape SimpleBody::GetDrawing(sf::Vector2f offset, float size) {
	sf::CircleShape c((mass / 200 + 4));;
	c.setPosition(pos+offset);
	return c;

}

void SimpleBody::UpdateBoost(SimpleBody& anotherBody) {
	float r = std::max(sqrtf((pos.x - anotherBody.pos.x) * (pos.x - anotherBody.pos.x) + (pos.y - anotherBody.pos.y) * (pos.y - anotherBody.pos.y)),float(0.1));
	float mod = pow(6.67, -11) * ((anotherBody.mass*pow(10,12)) / (r * r));
	boost += mod * ((anotherBody.pos - pos) / r);
}
