#include "Simulation.h"
#include "ParticlesSystem.h"






void Simulation::update(float EllapsedTime, bool timeStop) {
		concurrency::parallel_for_each(objects.begin(), objects.end(), [&](auto& body) {
			if (Simulation::timeSpeed != 0 && !timeStop) {
				for (auto& anotherBody : objects) {
					if (&body == &anotherBody) continue;
					body.UpdateBoost(anotherBody);
				}
				body.UpdateParams(EllapsedTime * Simulation::timeSpeed);
			}
		body.UpdateGraphic();
	});
	objects.erase(std::remove_if(objects.begin(), objects.end(), [&]( auto& i) {
		for (auto& anotherBody : objects) {
			if (&i == &anotherBody) continue;
			if (anotherBody.sprite.getGlobalBounds().intersects(i.sprite.getGlobalBounds())) {
				if (i.mass < 0.1*anotherBody.mass) {
					//anotherBody.speed = (float(anotherBody.mass) * anotherBody.speed + i.speed * float(i.mass))/float(anotherBody.mass);
					//anotherBody.mass += i.mass;
					ParticlesSystem::add(new Explosion(100,i.pos, sf::Vector3f(i.color[0], i.color[1], i.color[2])));
					
					return true;
				}
				
			}
		}
		return false;
	}), objects.end());

}
std::vector<Object> Simulation::objects;
float Simulation::timeSpeed=1;

