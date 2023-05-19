#include "Physics.h"
#include "ParticlesSystem.h"


void Physics::update(sf::Time EllapsedTime, bool timeStop) {
		concurrency::parallel_for_each(objects.begin(), objects.end(), [&](auto& body) {
			if (timeSpeed != 0 && !timeStop) {
				body.acceleration={0,0};
				for (Object& anotherBody : objects) {
					if (&body == &anotherBody) continue;
					calculateAcceleration(body, anotherBody);
				}
				body.updateSpeed(EllapsedTime.asSeconds() * timeSpeed);
				body.updatePosition(EllapsedTime.asSeconds() * timeSpeed);
			}
		body.updateGraphic();
		});
		if (Physics::timeSpeed != 0 && !timeStop) {
			objects.erase(std::remove_if(objects.begin(), objects.end(), [&](auto& i) {
				
				for (Object& anotherBody : objects) {
					if (&i == &anotherBody) continue;
					if ((anotherBody.pos.x - i.pos.x) * (anotherBody.pos.x - i.pos.x) + (anotherBody.pos.y - i.pos.y) * (anotherBody.pos.y - i.pos.y) <= (i.radius + anotherBody.radius) * (i.radius + anotherBody.radius)) {
						if (i.mass <= anotherBody.mass) {
							ParticlesSystem::add(new Explosion(1000, i.pos, sf::Vector3f(i.color[0], i.color[1], i.color[2])));
							Physics::forGravityCenter.erase(std::remove_if(Physics::forGravityCenter.begin(), Physics::forGravityCenter.end(), [&](const auto& obj) {return obj == &i; }), Physics::forGravityCenter.end());
							return true;
						}

					}
				}
				return false;
				}), objects.end());
		}
}

void Physics::calculateAcceleration(Object& obj1, Object& obj2) {
	float r = sqrtf((obj1.pos.x - obj2.pos.x) * (obj1.pos.x - obj2.pos.x) + (obj1.pos.y - obj2.pos.y) * (obj1.pos.y - obj2.pos.y));
	r = std::max(r, 0.1f);
	float rWorld = r*powf(10,6);
	float len = 6.67*pow(10, -11) * (obj2.mass * pow(10, 24) / (rWorld * rWorld));
	obj1.acceleration += len * ((obj2.pos - obj1.pos) / r);
}


sf::Vector2f Physics::calculateCenterOfGravity() {
	int m = 0;
	sf::Vector2f rm;
	for (Object* obj : forGravityCenter) {
		rm += obj->mass * obj->pos;
		m += obj->mass;
	}
	return rm / float(m);
}

std::vector<Object> Physics::objects;
std::vector<Object*> Physics::forGravityCenter;
float Physics::timeSpeed = 1;
