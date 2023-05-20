#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>

#include"Object.h"
#include <SFML/Graphics.hpp>

class Save
{
private:
	std::fstream m_file;
public:

	Save(std::filesystem::path p);
	sf::Vector2f load(std::vector<Object>& objects);
	void save(std::vector<Object>& objects, sf::Vector2f cameraPosition);
	void close();
	~Save();

};

