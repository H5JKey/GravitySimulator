#include "Physics.h"


void Physics::update(std::vector<Object>& objects, sf::Time EllapsedTime) {

	if (selectedCollisionOption == 0) {
		objects.erase(std::remove_if(objects.begin(), objects.end(), [&](auto& object) {
			for (Object& otherObject : objects) {
				if (&otherObject == &object) continue;
				if (object.collide(otherObject)) {
					if (otherObject.properties.mass >= object.properties.mass) {

						ParticlesSystem::add(new Explosion(400, object.properties.pos / powf(10, 3), object.properties.color));
						return true;
					}
				}

			}
			return false;
			}), objects.end());
	}

	Concurrency::parallel_for(0, int(objects.size()), [&](int i) {
		objects[i].properties.acceleration = { 0,0 };
		if (!timeStop && timeSpeed != 0) {
			if (selectedCollisionOption == 1) {
				for (int j = i + 1; j < objects.size(); j++) {
					if (objects[i].collide(objects[j]))
						calculateCollision(objects[i], objects[j]);
				}
			}
			if (gravityOn) {
				for (std::size_t j = 0; j < objects.size(); j++) {
					if (&objects[i] == &objects[j])
						continue;
					if (!objects[j].properties.affectsOthers) continue;
					if (objects[i].properties.affectedByGravity) {
						if (gravityRange==0 || VectorMath::length(objects[j].properties.pos - objects[i].properties.pos)/powf(10,3) <= gravityRange) {
							objects[i].properties.acceleration += calculateAcceleration(objects[i], objects[j]);
						}
					}
				}
			}
			for (Force force : forces) 
				objects[i].properties.acceleration += (force.getVec() / (force.devideByMass() ? objects[i].properties.mass : 1));
			objects[i].updateSpeed(EllapsedTime.asSeconds() * timeSpeed);
		}
	});

	Concurrency::parallel_for(0, int(objects.size()), [&](int i) {
		objects[i].updateGraphic();
		if (!timeStop && timeSpeed != 0) 
			objects[i].updatePosition(EllapsedTime.asSeconds() * timeSpeed);
	});
}


sf::Vector2f Physics::calculateAcceleration(const Object& obj1, const Object& obj2) {
	float r = sqrtf((obj1.properties.pos.x - obj2.properties.pos.x) * (obj1.properties.pos.x - obj2.properties.pos.x) + (obj1.properties.pos.y - obj2.properties.pos.y) * (obj1.properties.pos.y - obj2.properties.pos.y));
	r = std::max(r, 0.1f);
	float rWorld = r*powf(10, 3);
	float value = 6.67 * pow(10, -11) * (obj2.properties.mass * pow(10, 24) / (rWorld * rWorld));
	return value * ((obj2.properties.pos - obj1.properties.pos) / r);
}



sf::Vector2f Physics::calculateCenterOfGravity(std::vector<Object*>& forGravityCenter) {
	int m = 0;
	sf::Vector2f rm;
	for (Object* obj : forGravityCenter) {
		rm += obj->properties.mass * (obj->properties.pos / 1000.f);
		m += obj->properties.mass;
	}
	return rm / float(m);
}



void Physics::calculateCollision(Object& object1, Object& object2) {

	sf::Vector2f n = object2.properties.pos - object1.properties.pos;

	VectorMath::normalize(n);

	float m1 = object1.properties.mass;
	float m2 = object2.properties.mass;

	if (m1 == 0)
		m1 = 0.00001;
	if (m2 == 0)
		m2 = 0.00001;

	float J = VectorMath::dot(((m1 * m2) / (m1 + m2)) * (1.f + restitutionCoefficient) * (object2.properties.speed - object1.properties.speed), n);
	object1.properties.speed += (J / m1) * n;
	object2.properties.speed -= (J / m2) * n;
}


