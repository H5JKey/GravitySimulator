#pragma once
#include <vector>
#include "Object.h"
#include "Save.h"
#include <ppl.h>
#include "VectorMath.h"
#include "ParticlesSystem.h"



class Force {
	sf::Vector2f direction;
	float value;
public:
	Force(float value,sf::Vector2f direction) {
		VectorMath::normalize(direction);
		this->direction = direction;
		this->value = value;
	}

	sf::Vector2f getVec() {
		return direction * value;
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
