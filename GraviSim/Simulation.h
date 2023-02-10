#pragma once
#include <vector>
#include "Object.h"
#include "Save.h"
#include <ppl.h>

class Simulation
{
public:
	static float timeSpeed;
	static std::vector<Object> objects;

	static void update(sf::Time EllapsedTime, bool timeStop);

};
