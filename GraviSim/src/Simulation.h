#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include "Physics.h"
#include "Object.h"
#include "Save.h"
#include "ParticlesSystem.h"


#include <ppl.h>
#include <algorithm>
#include <iostream>
#include <filesystem>


#include "../lib/imgui/imgui.h"
#include "../lib/imgui/imgui-SFML.h"
#include "../lib/imgui/imgui_stdlib.h"




class Simulation
{
public:
	Simulation();
	void start();
private:

	sf::RenderWindow App;
	sf::View camera;
	sf::Time EllapsedTime;
	sf::Clock clock, delta;
	sf::Vector2f offset;
	sf::Vector2f Pos;
	Object* selectedObj;
	Object newObj;
	sf::Texture t;
	sf::Sprite background;
	int savedTimeSpeed;
	std::string s;
	sf::Font font;
	sf::Text fpsTracker;

	class CenterOfGravity : sf::Drawable {
		sf::Vector2f pos;
		sf::RectangleShape cross[2];
	public:
		bool show;

		CenterOfGravity() {
			show = false;

			cross[0].setFillColor(sf::Color::Red);
			cross[1].setFillColor(sf::Color::Red);
			cross[0].setSize({ 8, 1 });
			cross[1].setSize({ 1, 8 });
			cross[0].setOrigin(4, 0.5);
			cross[1].setOrigin(0.5, 4);
		}
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const {
			target.draw(cross[0]);
			target.draw(cross[1]);
		}
		void operator=(const sf::Vector2f pos) {
			this->pos = pos;
			cross[0].setPosition(pos);
			cross[1].setPosition(pos);
		}
	};

	bool timeStop = false;
	CenterOfGravity centerOfGravity;

	int musicVolume;
	bool showOrbits;
	bool showFPS;
	bool drawBackground;

	void loadSettings();
	void saveSettings();
	void updateGui();
	void updateEvents();
	void updateGraphics();
	void updatePhysics();
	void update();

public:
	~Simulation();
};

