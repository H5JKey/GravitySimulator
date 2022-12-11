#include "Simulation.h"

void Simulation::update(float EllapsedTime) {
	for (auto &body: objects) {
		for (auto& anotherBody : objects) {
			if (&body == &anotherBody) continue;
			body.UpdateBoost(anotherBody);
		}
		bool Collision=false;
		for (auto& anotherBody: objects) {
			if (&body==&anotherBody) continue;
			if ((anotherBody.pos-body.pos).length()<=(anotherBody.mass/200+4+body.mass/200+4)) {
				Collision=true;
				break;
			}
		}
		if (!checkCollision) {
	        body.Update(EllapsedTime);
		}
	}
}

std::vector<Object> Simulation::objects;