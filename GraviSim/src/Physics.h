#pragma once
#include <vector>
#include "Object.h"
#include "Save.h"
#include <ppl.h>






class Physics
{
public:
	float timeSpeed;
	bool timeStop;
	bool gravityOn;
	float restitutionCoefficient;




	Physics() {
		timeSpeed = 500;
		gravityOn = true;
		restitutionCoefficient = 1;
		timeStop = false;
	}

	void update(std::vector<Object>& objects, sf::Time EllapsedTime);

	sf::Vector2f calculateAcceleration(const Object& obj1, const Object& obj2);
	sf::Vector2f calculateCenterOfGravity(std::vector<Object*>& forGravityCenter);

	void handleCollision(Object& object1, Object& oblect2);
};
