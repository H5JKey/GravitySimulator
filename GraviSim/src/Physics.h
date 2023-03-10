#pragma once
#include <vector>
#include "Object.h"
#include "Save.h"
#include <ppl.h>

class Physics
{
public:
	static float timeSpeed;
	static std::vector<Object> objects;

	static void update(sf::Time EllapsedTime, bool timeStop);

	static void calculateForce(Object &obj1, Object &obj2);
};
