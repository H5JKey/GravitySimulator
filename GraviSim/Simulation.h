#pragma once
#include <vector>
#include "Object.h"
#include <ppl.h>

class Simulation
{
public:
	static float timeSpeed;
	static std::vector<Object> objects;

	static void update(float EllapsedTime, bool timeStop);
};


