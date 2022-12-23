#include "Simulation.h"
#include <iostream>


void Simulation::update(float EllapsedTime, float timeSpeed, bool timeStop) {
		concurrency::parallel_for_each(objects.begin(), objects.end(), [&](auto& body) {
			if (timeSpeed != 0 && !timeStop) {
				for (auto& anotherBody : objects) {
					if (&body == &anotherBody) continue;
					body.UpdateBoost(anotherBody);
				}
				body.UpdateParams(EllapsedTime * timeSpeed);
			}
		body.UpdateGraphic();
	});
	objects.erase(std::remove_if(objects.begin(), objects.end(), [&]( auto& i) {
		for (auto& anotherBody : objects) {
			if (&i == &anotherBody) continue;
			if (anotherBody.sprite.getGlobalBounds().intersects(i.sprite.getGlobalBounds())) {
				if (i.mass < anotherBody.mass) {
					//anotherBody.speed = (float(anotherBody.mass) * anotherBody.speed + i.speed * float(i.mass))/float(anotherBody.mass);
					return true;
				}
				
			}
		}
		return false;
	}), objects.end());

}
std::vector<Object> Simulation::objects;
