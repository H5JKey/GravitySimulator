#pragma once
#include <vector>
#include "Object.h"

class Simulation
{
public:
	static std::vector<Object> objects;

	static void update(float EllapsedTime);
	
};


