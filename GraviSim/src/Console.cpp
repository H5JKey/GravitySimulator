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
					(simulation->objects.end() - 1)->properties.pos = sf::Vector2f(stoi(args[1])*1000,stoi(args[2])*1000);
					return success;
				}
				else
					return error;
			}
		}
	}
	return error;
}

