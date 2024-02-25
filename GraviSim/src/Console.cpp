#include "Console.h"
#include "Simulation.h"

int Console::handleCommand(std::string command)
{
	if (command[0] == '/') {
		std::vector<std::string> args = split(command);
		if (args[0] == "/add") {
			if (simulation->copied) {
				if (args.size() == 1) {
					simulation->objects.push_back(simulation->copiedObject);
					(simulation->objects.end() - 1)->properties.pos = simulation->cursorPosition*powf(10,3);
					return success;
				}
				else if (args.size() == 3) {
					simulation->objects.push_back(simulation->copiedObject);
					(simulation->objects.end() - 1)->properties.pos = sf::Vector2f(stof(args[1])*1000,stof(args[2])*1000);
					return success;
				}
				else
					return error;
			}
		}
		else if (args[0] == "/fill") {
			if (simulation->copied) {
				for (float x = stof(args[1]); x <= stof(args[3]); x += stof(args[5])) {
					for (float y = stof(args[2]); y <= stof(args[4]); y += stof(args[6])) {
						simulation->objects.push_back(simulation->copiedObject);
						(simulation->objects.end() - 1)->properties.pos = sf::Vector2f(x * 1000, y * 1000);
					}
				}
			}
		}
		else if (args[0] == "/forces") {
			if (args[1] == "add") {
				simulation->physics.forces.push_back(Force(stof(args[4]), sf::Vector2f(stof(args[2]), stof(args[3]))));
			}
			else if (args[1] == "clear") {
				simulation->physics.forces.clear();
			}
			else if (args[1] == "pop") {
				simulation->physics.forces.pop_back();
			}
		}
	}
	return error;
}

