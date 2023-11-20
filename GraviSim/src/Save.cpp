#include "Save.h"
#include <iostream>


Save::Save(std::string path):m_file(path) {}


void Save::load(std::vector<Object>& objects, sf::Vector2f& center, sf::Time& time) {
	m_file.read((char*)&center, sizeof(sf::Vector2f));
	m_file.read((char*)&time, sizeof(sf::Time));
	std::size_t n;
	m_file.read((char*)&n, sizeof(n));
	objects.resize(n);

	for (int i=0; i<n; i++)
		m_file.read((char*)&objects[i].properties, sizeof(objects[i].properties));
	objects.resize(n);
}

void Save::save(std::vector<Object>& objects, sf::Vector2f center, sf::Time time) {
	m_file.clear();
	std::size_t n = objects.size();
	m_file.write((char*)&center, sizeof(sf::Vector2f));
	m_file.write((char*)&time, sizeof(sf::Time));
	m_file.write((char*)&n, sizeof(n));
	for (int i = 0; i < n; i++) {
		
		m_file.write((char*)&objects[i].properties, sizeof(objects[i].properties));
	}


	m_file.close();
}

void Save::close() {
	m_file.close();
}


Save::~Save() {
	close();
}
