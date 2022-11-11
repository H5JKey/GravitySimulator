#pragma once
#include <vector>
#include "SimpleBody.h"

class Simulation
{
public:
	static std::vector<SimpleBody> bodies;

	static void update(float EllapsedTime);
	
};


