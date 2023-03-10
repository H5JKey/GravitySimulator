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

	bool timeStop = false;

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

