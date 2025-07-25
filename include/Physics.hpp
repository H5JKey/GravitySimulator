#pragma once
#include <vector>
#include "Object.hpp"
#include "Save.hpp"
#include "VectorMath.hpp"
#include "ParticlesSystem.hpp"



class Force {
	sf::Vector2f direction;
	float value;
	bool m_devideByMass;
public:
	Force(float value,sf::Vector2f direction, bool devideByMass) {
		VectorMath::normalize(direction);
		this->direction = direction;
		this->value = value;
		this->m_devideByMass = devideByMass;
	}

	sf::Vector2f getVec() {
		return direction * value;
	}

	bool devideByMass() const {
		return m_devideByMass;
	}
};


class Physics
{
public:
	float timeSpeed;
	bool timeStop;
	bool gravityOn;
	float restitutionCoefficient;
	int selectedCollisionOption;
	float gravityRange;

	std::vector<Force> forces;


	Physics() {
		timeSpeed = 500;
		gravityOn = true;
		restitutionCoefficient = 1;
		timeStop = false;
		selectedCollisionOption = 0;
		gravityRange = 0;
	}

	void update(std::vector<Object>& objects, sf::Time EllapsedTime);

	sf::Vector2f calculateAcceleration(const Object& obj1, const Object& obj2);
	sf::Vector2f calculateCenterOfGravity(std::vector<Object*>& forGravityCenter);

	void calculateCollision(Object& object1, Object& oblect2);
};
