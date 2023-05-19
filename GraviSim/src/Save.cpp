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
		m_file >> obj.name >> obj.pos.x >> obj.pos.y >> obj.mass >> obj.speed.x >> obj.speed.y >> obj.radius >> color[0] >> color[1] >> color[2] >> obj.fixed;
		if (obj.name == "##noName##") obj.name = "";
		obj.color.r = static_cast<sf::Uint8>(color[0]);
		obj.color.g = static_cast<sf::Uint8>(color[1]);
		obj.color.b = static_cast<sf::Uint8>(color[2]);
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
		std::string name = obj.name;
		if (obj.name == "") name = "##noName##";
		color[0] = static_cast<int>(obj.color.r);
		color[1] = static_cast<int>(obj.color.g);
		color[2] = static_cast<int>(obj.color.b);
		m_file << name << ' ' << obj.pos.x << ' ' << obj.pos.y << ' ' << obj.mass << ' ' << obj.speed.x << ' ' << obj.speed.y << ' '  << ' ' << obj.radius << ' ' << color[0] << ' ' << color[1] << ' ' << color[2] << ' ' << obj.fixed;

		if (&obj != &*(objects.end() - 1))
			m_file << '\n';

	}
}


Save::~Save() {
	if (m_file.is_open())
		m_file.close();
}
