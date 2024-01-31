#pragma once
#include <vector>
#include <string>

class Simulation;

class Console {
private:
	Simulation* simulation;

	std::vector<std::string> split(std::string s) {
		std::vector<std::string> vec(0);
		if (s[s.length() - 1] != ' ')
			s += ' ';
		while (s != "") {
			vec.push_back(s.substr(0, s.find(' ')));
			s = s.substr(s.find(' ') + 1);
		}
		return vec;
	}


public:
	bool show;
	enum {
		error=1,
		success=0
	};

	Console(Simulation* simulation) {
		show = false;
		this->simulation = simulation;
	}

	int handleCommand(std::string command);
	
	int add(std::vector<std::string>& args);
};
