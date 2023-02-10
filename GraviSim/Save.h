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
	std::fstream* m_file;
public:
	std::string name;

	Save(std::filesystem::path p) {
		m_file = new std::fstream(p);
	}

	void readInfo() {
		*m_file >> name;
	}

	sf::Vector2f& readCameraInfo() {
		sf::Vector2f pos;
		*m_file >> pos.x >> pos.y;
		return pos;
	}
	
	void loadWorld(std::vector<Object>& objects) {
		objects.clear();
		while (!m_file->eof()) {
			Object obj;
			*m_file >> obj.name >> obj.pos.x >> obj.pos.y >> obj.mass >> obj.speed.x >> obj.speed.y >> obj.boost.x >> obj.boost.y >> obj.radius >> obj.color[1] >> obj.color[2] >> obj.color[3] >> obj.fixed;
	
			objects.push_back(obj);
		}
	}

	void save(std::vector<Object>& objects, sf::Vector2f camPos) {
		m_file->clear();
		*m_file << name<<'\n';
		*m_file << camPos.x <<' '<<camPos.y;
		if (objects.size() != 0)
			*m_file << '\n';
		for (Object &obj : objects) {
			std::string name = obj.name;
			if (obj.name == "") name = "##noName##";
			*m_file << name <<' '<< obj.pos.x <<' '<< obj.pos.y <<' '<< obj.mass <<' '<< obj.speed.x <<' '<< obj.speed.y <<' '<< obj.boost.x <<' '<< obj.boost.y <<' '<< obj.radius <<' '<< obj.color[1] <<' '<< obj.color[2] <<' '<< obj.color[3] <<' ' << obj.fixed;
			if (&obj != &*(objects.end() - 1))
				*m_file << '\n';
		}
	}

	void close() {
		if (m_file->is_open())
			m_file->close();
	}

	~Save() {
		close();
		delete(m_file);
	}


};

