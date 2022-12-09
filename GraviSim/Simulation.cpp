#include "Simulation.h"

void Simulation::update(float EllapsedTime) {
	for (auto &body: objects) {
		for (auto& anotherBody : objects) {
			if (&body == &anotherBody) continue;
			body.UpdateBoost(anotherBody);
		}
		body.Update(EllapsedTime);
	}
}

std::vector<Object> Simulation::objects;