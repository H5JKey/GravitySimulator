#include "Save.h"

Save::Save(std::filesystem::path p) : m_file(p) {
	std::getline(m_file, name);
}


sf::Vector2f Save::load(std::vector<Object>& objects) {
	objects.clear();
	sf::Vector2f info;
	m_file >> info.x >> info.y;

	while (!m_file.eof()) {
		Object obj;
		m_file >> obj.name >> obj.pos.x >> obj.pos.y >> obj.mass >> obj.speed.x >> obj.speed.y >> obj.acceleration.x >> obj.acceleration.y >> obj.radius >> obj.color[0] >> obj.color[1] >> obj.color[2] >> obj.fixed;
		if (obj.name == "##noName##") obj.name = "";
		objects.push_back(obj);
	}
	return info;
}

void Save::save(std::vector<Object>& objects, sf::Vector2f camPos) {
	m_file.clear();
	m_file << name << '\n';
	m_file << camPos.x << ' ' << camPos.y;
	if (objects.size() != 0)
		m_file << '\n';
	for (Object& obj : objects) {
		std::string name = obj.name;
		if (obj.name == "") name = "##noName##";
		m_file << name << ' ' << obj.pos.x << ' ' << obj.pos.y << ' ' << obj.mass << ' ' << obj.speed.x << ' ' << obj.speed.y << ' ' << obj.acceleration.x << ' ' << obj.acceleration.y << ' ' << obj.radius << ' ' << obj.color[0] << ' ' << obj.color[1] << ' ' << obj.color[2] << ' ' << obj.fixed;
		if (&obj != &*(objects.end() - 1))
			m_file << '\n';
	}
}


Save::~Save() {
	if (m_file.is_open())
		m_file.close();
}
