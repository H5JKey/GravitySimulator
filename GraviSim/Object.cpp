#include "Object.h"
#include <iostream>


Object::Object(int mass, sf::Vector2f pos, sf::Vector2f speed, std::string name, sf::Color color, bool fixed) {
	this->pos = pos;
	this->mass = mass;
	this->speed = speed;
	this->name = name;
	this->fixed = fixed;
	this->color[0] = color.r; this->color[1] = color.g; this->color[2] = color.b;
	Object::UpdateGraphic();
}

void Object::UpdateParams(float EllapsedTime) {
	if (!this->fixed) {
		this->speed += this->boost * EllapsedTime;
		this->pos += this->speed * EllapsedTime;
	}
	this->boost = sf::Vector2f(0,0);
	
}

void Object::UpdateGraphic() {
	sprite.setRadius(this->mass / 1000 + 4);
	sprite.setPosition(pos-sf::Vector2f(sprite.getRadius(),sprite.getRadius()));
	sprite.setFillColor(sf::Color(static_cast<sf::Uint8>(this->color[0] * 255.f), static_cast<sf::Uint8>(this->color[1] * 255.f), static_cast<sf::Uint8>(this->color[2] * 255.f)));
}


void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite);
}


Object::Object() {
	this->mass = 0;
	this->fixed = false;
	this->name = "";
	this->color[0] = this->color[1] = this->color[2] = 1;
}

void Object::UpdateBoost(Object& anotherBody) {
	float r = std::max(sqrtf((pos.x - anotherBody.pos.x) * (pos.x - anotherBody.pos.x) + (pos.y - anotherBody.pos.y) * (pos.y - anotherBody.pos.y)),float(0.1));
	float mod = pow(6.67, -11) * ((anotherBody.mass*pow(10,12)) / (r * r));
	boost += mod * ((anotherBody.pos - pos) / r);
}
