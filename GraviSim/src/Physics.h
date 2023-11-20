#pragma once
#include <vector>
#include "Object.h"
#include "Save.h"
#include <ppl.h>

class Physics
{
public:
	static float timeSpeed;
	static bool gravityOn;
	static float restitutionCoefficient;

	static void update(Object& object, std::vector<Object>& objects, sf::Time EllapsedTime);

	static sf::Vector2f calculateAcceleration(const Object& obj1, const Object& obj2);
	static sf::Vector2f calculateCenterOfGravity(std::vector<Object*>& forGravityCenter);

	static void handleCollision(Object& object1, Object& oblect2);
};
