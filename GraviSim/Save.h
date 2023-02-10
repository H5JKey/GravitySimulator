#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <iostream>
#include"Object.h"
#include <SFML/Graphics.hpp>

class Save
{
private:
	std::fstream* m_save;
public:
	std::string name;

	Save(std::filesystem::path p) {
		m_save = new std::fstream(p);
	}

	void readInfo() {
		*m_save >> name;
	}

	sf::Vector2f& readCameraInfo() {
		sf::Vector2f pos;
		*m_save >> pos.x >> pos.y;
		return pos;
	}
	
	void loadWorld(std::vector<Object>& objects) {
		objects.clear();
		while (!m_save->eof()) {
			Object obj;
			*m_save >> obj.name >> obj.pos.x >> obj.pos.y >> obj.mass >> obj.speed.x >> obj.speed.y >> obj.boost.x >> obj.boost.y >> obj.radius >> obj.color[1] >> obj.color[2] >> obj.color[3] >> obj.fixed;
	
			objects.push_back(obj);
		}
	}

	void save(std::vector<Object>& objects, sf::Vector2f camPos) {
		m_save->clear();
		*m_save << name<<'\n';
		*m_save << camPos.x <<' '<<camPos.y;
		if (objects.size() != 0)
			*m_save << '\n';
		for (Object &obj : objects) {
			std::string name = obj.name;
			if (obj.name == "") name = "##noName##";
			*m_save << name <<' '<< obj.pos.x <<' '<< obj.pos.y <<' '<< obj.mass <<' '<< obj.speed.x <<' '<< obj.speed.y <<' '<< obj.boost.x <<' '<< obj.boost.y <<' '<< obj.radius <<' '<< obj.color[1] <<' '<< obj.color[2] <<' '<< obj.color[3] <<' ' << obj.fixed;
			if (&obj != &*(objects.end() - 1))
				*m_save << '\n';
		}
	}

	~Save() {
		if (m_save->is_open())
			delete(m_save);
	}


};

