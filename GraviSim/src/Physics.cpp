#include "Physics.h"
#include "ParticlesSystem.h"


void Physics::update(sf::Time EllapsedTime, bool timeStop) {
		concurrency::parallel_for_each(objects.begin(), objects.end(), [&](auto& body) {
			if (timeSpeed != 0 && !timeStop) {
				for (auto& anotherBody : objects) {
					if (&body == &anotherBody) continue;
					body.UpdateBoost(anotherBody);
				}
				body.UpdateParams(EllapsedTime.asSeconds() * Physics::timeSpeed);
			}
		body.UpdateGraphic();
		});
		if (Physics::timeSpeed != 0 && !timeStop) {
			objects.erase(std::remove_if(objects.begin(), objects.end(), [&](auto& i) {
				for (auto& anotherBody : objects) {
					if (&i == &anotherBody) continue;
					if ((anotherBody.pos.x - i.pos.x) * (anotherBody.pos.x - i.pos.x) + (anotherBody.pos.y - i.pos.y) * (anotherBody.pos.y - i.pos.y) <= (i.radius + anotherBody.radius) * (i.radius + anotherBody.radius)) {
						if (i.mass <= anotherBody.mass) {
							ParticlesSystem::add(new Explosion(1000, i.pos, sf::Vector3f(i.color[0], i.color[1], i.color[2])));
							return true;
						}

					}
				}
				return false;
				}), objects.end());
			ParticlesSystem::update(EllapsedTime, timeSpeed);
		}
}

std::vector<Object> Physics::objects;
float Physics::timeSpeed = 1;
