#include "Object.h"
#include <iostream>


Object::Object(float mass, float radius, sf::Vector2f pos, sf::Vector2f speed, std::string name, sf::Color color, bool fixed) : m_picture(radius, 900) {
	this->properties.pos = pos*powf(10,3);
	this->properties.mass = mass;
	this->properties.speed = speed;
	this->properties.name = name;
	this->properties.fixed = fixed;
	this->properties.radius = radius;
	this->properties.acceleration = { 0,0 };
	this->properties.color = color;
	this->properties.affectedByGravity = true;
	this->properties.affectsOthers = true;

	useForGravityCenter=false;
}

Object::Object(Properties properties) : m_picture(properties.radius, 900) {
	this->properties = properties;

	useForGravityCenter = false;
}

void Object::updatePosition(float EllapsedTime) {
	if (!this->properties.fixed) {
		this->properties.pos += (this->properties.speed * EllapsedTime);
	}
}

void Object::updateSpeed(float EllapsedTime) {
	if (!this->properties.fixed) {
		this->properties.speed += (EllapsedTime * this->properties.acceleration)/powf(10,3);
	}
}

void Object::updateGraphic() {
	m_picture.setRadius(properties.radius);
	m_picture.setPosition(properties.pos/powf(10,3) - sf::Vector2f(m_picture.getRadius(), m_picture.getRadius()));
	m_picture.setFillColor(properties.color);
}


void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_picture);
}

bool Object::collide(Object& anotherObject) {
	return (anotherObject.properties.pos.x - this->properties.pos.x) * (anotherObject.properties.pos.x - this->properties.pos.x) + (anotherObject.properties.pos.y - this->properties.pos.y) * (anotherObject.properties.pos.y - this->properties.pos.y) <= powf(10,6)*(this->properties.radius + anotherObject.properties.radius) *(this->properties.radius + anotherObject.properties.radius);
}

bool Object::collide(sf::Vector2f point) {
	return this->m_picture.getGlobalBounds().contains(point);
}

Object::Object() :m_picture(properties.radius, 90) {
	this->properties.mass = 0;
	this->properties.fixed = false;
	this->properties.name = "";
	this->properties.color = { 255,255,255 };
	this->properties.radius = abs(this->properties.mass) / 6000 + 1;
	this->properties.affectedByGravity = true;
	this->properties.affectsOthers = true;
	useForGravityCenter=false;

}

void Object::operator=(Object other) {
	this->properties = other.properties;
	m_picture = other.m_picture;
	useForGravityCenter = other.useForGravityCenter;
}

void Object::operator=(Properties other) {
	this->properties = other;
}