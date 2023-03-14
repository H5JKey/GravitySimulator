#include "Object.h"
#include <iostream>


Object::Object(float mass, sf::Vector2f pos, sf::Vector2f speed, std::string name, sf::Color color, bool fixed, float radius) {
	this->pos = pos;
	this->mass = mass;
	this->speed = speed;
	this->name = name;
	this->fixed = fixed;
	if (radius == -1)
		this->radius = std::max(1.f,std::min(750.f,abs(this->mass) / 1000 + 1));
	else
		this->radius = radius;
	this->color[0] = color.r; this->color[1] = color.g; this->color[2] = color.b;
	Object::UpdateGraphic();
}

void Object::UpdatePosition(float EllapsedTime) {
	if (!this->fixed) {
		this->pos += this->speed * EllapsedTime+0.5*this->boost*EllapsedTime*EllapsedTime;
	}
}

void Object::UpdateSpeed(float EllapsedTime) {
	if (!speed->fixed) {
		this->speed+=EllapsedTime*0.5(this->boost+this->d_boost);
	}
}

void Object::UpdateGraphic() {
	sprite.setRadius(radius);
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
	this->radius = abs(this->mass) / 1000 + 1;;
}