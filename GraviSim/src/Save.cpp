#include "Save.h"


Save::Save(std::string path):m_file(path) {}


void Save::load(std::vector<Object>& objects, sf::Vector2f& center, sf::Time& time) {
	m_file.read((char*)&center, sizeof(sf::Vector2f));
	m_file.read((char*)&time, sizeof(sf::Time));
	objects.clear();


	Properties savingObj;
	while (m_file.read((char*)&savingObj, sizeof(savingObj))) {
		Object obj;
		obj.mass = savingObj.mass;
		obj.name = savingObj.name;
		obj.speed = savingObj.speed;
		obj.color = savingObj.color;
		obj.radius = savingObj.radius;
		obj.pos = savingObj.pos;
		objects.push_back(obj);
	}
	m_file.close();
}

void Save::save(std::vector<Object>& objects, sf::Vector2f center, sf::Time time) {
	m_file.clear();
	m_file.write((char*)&center, sizeof(sf::Vector2f));
	m_file.write((char*)&time, sizeof(sf::Time));

	for (Object& obj : objects) {

		Properties savingObj;
		savingObj.mass = obj.mass;
		savingObj.pos = obj.pos;
		savingObj.speed = obj.speed;
		savingObj.color = obj.color;
		savingObj.name = obj.name;
		savingObj.radius = obj.radius;

		m_file.write((char*)&savingObj, sizeof(savingObj));
	}
	m_file.close();
}

void Save::close() {
	m_file.close();
}


Save::~Save() {
	close();
}
