#include "Save.h"

struct ObjectSavingParams {
	float mass;
	sf::Vector2f pos;
	sf::Vector2f speed;
	std::string name;
	sf::Color color;
	float radius;
};

Save::Save(std::filesystem::path p):m_file(p) {}


void Save::load(std::vector<Object>& objects, sf::Vector2f& center, sf::Time& time) {
	m_file.read((char*)&center, sizeof(sf::Vector2f));
	m_file.read((char*)&time, sizeof(sf::Time));
	objects.clear();
	ObjectSavingParams params;
	Object obj;

	
	while (m_file.read((char*)&params, sizeof(ObjectSavingParams))) {
		obj.mass = params.mass;
		obj.name = params.name;
		obj.speed = params.speed;
		obj.color = params.color;
		obj.radius = params.radius;
		obj.pos = params.pos;
		objects.push_back(obj);
	}
}

void Save::save(std::vector<Object>& objects, sf::Vector2f center, sf::Time time) {
	m_file.clear();
	m_file.write((char*)&center, sizeof(sf::Vector2f));
	m_file.write((char*)&time, sizeof(sf::Time));

	for (Object& obj : objects) {
		ObjectSavingParams params;
		params.mass = obj.mass;
		params.pos = obj.pos;
		params.speed = obj.speed;
		params.color = obj.color;
		params.name = obj.name;
		params.radius = obj.radius;

		m_file.write((char*)&params, sizeof(ObjectSavingParams));
	}
}

void Save::close() {
	if (m_file.is_open())
		m_file.close();
}


Save::~Save() {
	close();
}
