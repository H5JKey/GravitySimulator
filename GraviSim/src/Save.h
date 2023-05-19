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
	std::string name;

	Save(std::filesystem::path p);
	sf::Vector2f load(std::vector<Object>& objects);
	void save(const std::vector<Object>& objects, const sf::Vector2f cameraPosition);
	~Save();

};

