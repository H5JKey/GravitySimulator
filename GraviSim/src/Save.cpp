#include "Save.h"


Save::Save(std::filesystem::path p):m_file(p) {}


void Save::load(std::vector<Object>& objects, sf::Vector2f& center, sf::Time& time) {
	m_file.read((char*)&center, sizeof(sf::Vector2f));
	m_file.read((char*)&time, sizeof(sf::Time));
	objects.clear();
	Properties savingObj;
	Object obj;

	
	while (m_file.read((char*)&savingObj, sizeof(savingObj))) {
		obj.mass = savingObj.mass;
		obj.name = savingObj.name;
		obj.speed = savingObj.speed;
		obj.color = savingObj.color;
		obj.radius = savingObj.radius;
		obj.pos = savingObj.pos;
		objects.push_back(obj);
	}
}

void Save::save(std::vector<Object>& objects, sf::Vector2f center, sf::Time time) {
	m_file.clear();
	m_file.write((char*)&center, sizeof(sf::Vector2f));
	m_file.write((char*)&time, sizeof(sf::Time));

	Properties savingObj;
	for (Object& obj : objects) {

		savingObj.mass = obj.mass;
		savingObj.pos = obj.pos;
		savingObj.speed = obj.speed;
		savingObj.color = obj.color;
		savingObj.name = obj.name;
		savingObj.radius = obj.radius;

		m_file.write((char*)&savingObj, sizeof(savingObj));
	}
}

void Save::close() {
	if (m_file.is_open())
		m_file.close();
}


Save::~Save() {
	close();
}
