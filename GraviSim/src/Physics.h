#pragma once
#include <vector>
#include "Object.h"
#include "Save.h"
#include <ppl.h>

class Physics
{
public:
	static float timeSpeed;

	static void update(std::vector<Object>& objects, sf::Time EllapsedTime, bool timeStop);

	static void calculateAcceleration(Object& obj1, Object& obj2);
	static sf::Vector2f calculateCenterOfGravity(std::vector<Object*>& forGravityCenter);
};
