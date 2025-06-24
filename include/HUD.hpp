#pragma once
#include <SFML/Graphics.hpp>

class HUD : public sf::Drawable
{
protected:
	sf::Font font;
	sf::Text str;
public:
	bool show;
	HUD();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

};

class FpsTracker : public HUD {

public:
	FpsTracker();

	void calculate(sf::Time ellapsedTime);
};

class Timer : public HUD {
private:
	sf::Time time;
public:
	Timer();

	void display();

	void reset();

	void set(sf::Time time);

	sf::Time get();

	void operator+=(sf::Time ellapsedTime) {
		time += ellapsedTime;
		display();
	}

};




