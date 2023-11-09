#include "Physics.h"
#include "ParticlesSystem.h"

void Physics::update(Object& object,std::vector<Object>& objects, sf::Time EllapsedTime) {
	object.acceleration = { 0,0 };
	if (gravityOn) {
		for (Object& otherObject : objects) {
			if (&object == &otherObject) continue;
			object.acceleration += calculateAcceleration(object, otherObject);
		}
	}
	object.updateSpeed(EllapsedTime.asSeconds() * timeSpeed);
	object.updatePosition(EllapsedTime.asSeconds() * timeSpeed);
}

sf::Vector2f Physics::calculateAcceleration(const Object& obj1, const Object& obj2) {
	float r = sqrtf((obj1.pos.x - obj2.pos.x) * (obj1.pos.x - obj2.pos.x) + (obj1.pos.y - obj2.pos.y) * (obj1.pos.y - obj2.pos.y));
	r = std::max(r, 0.1f);
	float rWorld = r*powf(10, 3);
	float len = 6.67 * pow(10, -11) * (obj2.mass * pow(10, 24) / (rWorld * rWorld));
	return len * ((obj2.pos - obj1.pos) / r);
}


sf::Vector2f Physics::calculateCenterOfGravity(std::vector<Object*>& forGravityCenter) {
	int m = 0;
	sf::Vector2f rm;
	for (Object* obj : forGravityCenter) {
		rm += obj->mass * (obj->pos / 1000.f);
		m += obj->mass;
	}
	return rm / float(m);
}

float Physics::timeSpeed = 500;
bool Physics::gravityOn = true;

