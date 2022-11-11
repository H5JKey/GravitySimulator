#include "SimpleBody.h"


SimpleBody::SimpleBody(int mass, sf::Vector2f pos, sf::Vector2f speed) {
	this->pos = pos;
	this->mass = mass;
	this->speed = speed;
}

void SimpleBody::Update(float EllapsedTime,SimpleBody& anotherBody) {
	float r = sqrtf((pos.x - anotherBody.pos.x) * (pos.x - anotherBody.pos.x) + (pos.y - anotherBody.pos.y) * (pos.y - anotherBody.pos.y));
	float force = pow(6.67, -11) * (anotherBody.mass * this->mass) / (r * r);


	this->speed += this->boost * EllapsedTime;
	this->pos += this->speed * EllapsedTime;
}

