#include "Physics.h"
#include "ParticlesSystem.h"

void Physics::update(std::vector<Object>& objects, sf::Time EllapsedTime, bool timeStop) {
	concurrency::parallel_for_each(objects.begin(), objects.end(), [&](Object& object) {
		if (timeSpeed != 0 && !timeStop) {
			object.acceleration = { 0,0 };
			for (Object& anotherObject : objects) {
				if (&object == &anotherObject) continue;
				calculateAcceleration(object, anotherObject);
			}
			object.updateSpeed(EllapsedTime.asSeconds() * timeSpeed);
			object.updatePosition(EllapsedTime.asSeconds() * timeSpeed);
		}
		object.updateGraphic();
		});
}

void Physics::calculateAcceleration(Object& obj1, Object& obj2) {
	float r = sqrtf((obj1.pos.x - obj2.pos.x) * (obj1.pos.x - obj2.pos.x) + (obj1.pos.y - obj2.pos.y) * (obj1.pos.y - obj2.pos.y));
	r = std::max(r, 0.1f);
	float rWorld = r * pow(10, 6);
	float len = 6.67 * pow(10, -11) * (obj2.mass * pow(10, 24) / (rWorld * rWorld));
	obj1.acceleration += len * ((obj2.pos - obj1.pos) / r);
}


sf::Vector2f Physics::calculateCenterOfGravity(std::vector<Object*>& forGravityCenter) {
	int m = 0;
	sf::Vector2f rm;
	for (Object* obj : forGravityCenter) {
		rm += obj->mass * obj->pos;
		m += obj->mass;
	}
	return rm / float(m);
}

float Physics::timeSpeed = 500;

