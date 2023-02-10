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

	static void setup() {
		objects.push_back(Object(100000, sf::Vector2f(960,540), sf::Vector2f(0, 0), "Sun"));
		objects.push_back(Object(300, sf::Vector2f(960, 50), sf::Vector2f(320, 0), "Planet"));
	}

};
