#include "Save.h"


Save::Save(std::filesystem::path p):m_file(p) {
	std::getline(m_file, name);
}


sf::Vector2f Save::load(std::vector<Object>& objects) {
	sf::Vector2f cameraPosition;
	m_file >> cameraPosition.x >> cameraPosition.y;
	objects.clear();
	Object obj;
	int color[3] = { 0,0,0 };
	while (!m_file.eof()) {
		m_file >> obj;
		objects.push_back(obj);
	}
	return cameraPosition;
}

void Save::save(std::vector<Object>& objects, sf::Vector2f cameraPosition) {
	m_file.clear();
	m_file << name << '\n';
	m_file << cameraPosition.x << ' ' << cameraPosition.y;
	if (objects.size() != 0)
		m_file << '\n';
	int color[3];
	for (Object& obj : objects) {
		m_file << obj;
		if (&obj != &*(objects.end() - 1))
			m_file << '\n';

	}
}

void Save::close() {
	if (m_file.is_open())
		m_file.close();
}


Save::~Save() {
	close();
}
