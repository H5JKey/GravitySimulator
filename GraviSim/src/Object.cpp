#include "Object.h"
#include <iostream>


Object::Object(float mass, int radius, sf::Vector2f pos, sf::Vector2f speed, std::string name, sf::Color color, bool fixed) : m_picture(radius, 90) {
	this->pos = pos*powf(10,3);
	this->mass = mass;
	this->speed = speed;
	this->name = name;
	this->fixed = fixed;
	this->radius = radius;
	this->acceleration = { 0,0 };
	this->color = color;

	useForGravityCenter=false;

}

void Object::updatePosition(float EllapsedTime) {
	if (!this->fixed) {
		this->pos += (this->speed * EllapsedTime);
	}
}

void Object::updateSpeed(float EllapsedTime) {
	if (!this->fixed) {
		this->speed += (EllapsedTime * this->acceleration)/powf(10,3);
	}
}

void Object::updateGraphic() {
	m_picture.setRadius(radius);
	m_picture.setPosition(pos/powf(10,3) - sf::Vector2f(m_picture.getRadius(), m_picture.getRadius()));
	m_picture.setFillColor(color);
}


void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_picture);
}

bool Object::collide(Object& anotherObject) {
	return (anotherObject.pos.x - this->pos.x) * (anotherObject.pos.x - this->pos.x) + (anotherObject.pos.y - this->pos.y) * (anotherObject.pos.y - this->pos.y) <= powf(10,3)*(this->radius + anotherObject.radius) * powf(10,3)*(this->radius + anotherObject.radius);
}

bool Object::collide(sf::Vector2f point) {
	return this->m_picture.getGlobalBounds().contains(point);
}

Object::Object() :m_picture(radius, 90) {
	this->mass = 0;
	this->fixed = false;
	this->name = "";
	this->color = { 255,255,255 };
	this->radius = abs(this->mass) / 6000 + 1;

	useForGravityCenter=false;

}

void Object::operator=(Object other) {
	mass = other.mass;
	radius = other.radius;
	pos = other.pos;
	speed = other.speed;
	acceleration = other.acceleration;
	name = other.name;
	color = other.color;
	fixed = other.fixed;
	m_picture = other.m_picture;
	useForGravityCenter = other.useForGravityCenter;
}

void Object::operator=(Properties other) {
	mass = other.mass;
	radius = other.radius;
	pos = other.pos;
	speed = other.speed;
	acceleration = other.acceleration;
	name = other.name;
	color = other.color;
	fixed = other.fixed;
}