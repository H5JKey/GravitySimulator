#pragma once
#include <vector>
#include "Object.h"
#include <ppl.h>

class Simulation
{
public:
	static std::vector<Object> objects;

	static void update(float EllapsedTime, float timeSpeed, bool timeStop);
	
};


