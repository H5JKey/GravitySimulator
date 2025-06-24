#pragma once
#include <string>
#include <fstream>
#include <vector>

#include"Object.hpp"
#include <SFML/Graphics.hpp>

class Save
{
private:
	std::fstream m_file;
public:

	Save(std::string path);
	void load(std::vector<Object>& objects, sf::Vector2f& center, sf::Time& time);
	void save(std::vector<Object>& objects, sf::Vector2f cameraPosition, sf::Time time);
	void close();
	~Save();

};

