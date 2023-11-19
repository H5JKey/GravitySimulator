#include "Save.h"
#include <iostream>


Save::Save(std::string path):m_file(path) {}


void Save::load(std::vector<Object>& objects, sf::Vector2f& center, sf::Time& time) {
	m_file.read((char*)&center, sizeof(sf::Vector2f));
	m_file.read((char*)&time, sizeof(sf::Time));
	std::size_t n;
	m_file.read((char*)&n, sizeof(n));
	objects.clear();

	Properties* objectsProperties_arr = new Properties[n];
	m_file.read((char*)objectsProperties_arr, n * sizeof(Properties));
	objects.resize(n);
	for (int i = 0; i < n; i++) {
		objects[i] = objectsProperties_arr[i];
	}
	
}

void Save::save(std::vector<Object>& objects, sf::Vector2f center, sf::Time time) {
	m_file.clear();
	std::size_t n = objects.size();
	m_file.write((char*)&center, sizeof(sf::Vector2f));
	m_file.write((char*)&time, sizeof(sf::Time));
	m_file.write((char*)&n, sizeof(n));
	Properties* objectsProperties_arr =new Object[n];
	for (int i = 0; i < n; i++)
		objectsProperties_arr[i] = objects[i];
	m_file.write((const char*)objectsProperties_arr, n * sizeof(Properties));
	
	m_file.close();
}

void Save::close() {
	m_file.close();
}


Save::~Save() {
	close();
}
