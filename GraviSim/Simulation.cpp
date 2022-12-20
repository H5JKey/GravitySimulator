#include "Simulation.h"


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
}

std::vector<Object> Simulation::objects;