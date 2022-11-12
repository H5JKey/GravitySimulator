#include "Simulation.h"

void Simulation::update(float EllapsedTime) {
	for (auto &body: bodies) {
		for (auto& anotherBody : bodies) {
			if (&body == &anotherBody) continue;
			body.UpdateBoost(anotherBody);
		}
		body.Update(EllapsedTime);
	}
}

std::vector<SimpleBody> Simulation::bodies;