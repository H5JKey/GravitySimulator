#include "HUD.h"



HUD::HUD() {
	show = false;
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	str.setFont(font);

}


void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(str);
}


FpsTracker::FpsTracker() :HUD() {
	str.setCharacterSize(17);
	str.setStyle(sf::Text::Bold);
	str.setFillColor(sf::Color::White);
	str.setPosition(10, 7);
}

void FpsTracker::calculate(sf::Time ellapsedTime) {
	str.setString(std::to_string(int(1 / ellapsedTime.asSeconds())));
}



Timer::Timer() :HUD() {

	str.setCharacterSize(17);
	str.setStyle(sf::Text::Bold);
	str.setFillColor(sf::Color::White);
	str.setPosition(10, 28);
}

void Timer::display() {
	int s = time.asSeconds();

	int m = s / 60;
	s %= 60;
	int h = m / 60;
	m %= 60;
	int d = h / 24;
	h %= 24;

	str.setString(std::to_string(d) + ':' + std::to_string(h) + ':' + std::to_string(m) + ':' + std::to_string(s));
}

void Timer::reset() {
	time = sf::Time::Zero;
	str.setString("0:0:0:0");
}

void Timer::set(sf::Time time) {
	this->time = time;
	display();
}

sf::Time Timer::get() {
	return time;
}

