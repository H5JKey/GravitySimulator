#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include "Physics.hpp"
#include "Object.hpp"
#include "Save.hpp"
#include "ParticlesSystem.hpp"
#include "VectorMath.hpp"
#include "HUD.hpp"
#include "Console.hpp"

#include <algorithm>
#include <iostream>
#include <filesystem>

#include "imgui.h"
#include "imgui-SFML.h"
#include "misc/cpp/imgui_stdlib.h"
//#include "ImGuiFileDialog.h"


class Simulation
{
public:
	Simulation();
	void start();
	~Simulation();
private:
	struct BackGround : sf::Drawable {
	private:
		sf::Texture texture;
		sf::Sprite sprite;
	public:
		bool show;
		BackGround(const std::string filePath, sf::View& view) {
			show = false;
			texture.loadFromFile(filePath);
			sprite.setScale(view.getSize().x / texture.getSize().x, view.getSize().y / texture.getSize().y);
			sprite.setTexture(texture);
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const {
			target.draw(sprite);
		}
	};

	struct CenterOfGravity : sf::Drawable {
	private:
		sf::Vector2f pos;
		sf::RectangleShape cross[2];
		float size;
	public:
		bool show;

		CenterOfGravity() {
			show = false;
			size = 8;
			cross[0].setFillColor(sf::Color::Red);
			cross[1].setFillColor(sf::Color::Red);
			cross[0].setSize({ size, 1 });
			cross[1].setSize({ 1, size });
			cross[0].setOrigin(size / 2, 0.5);
			cross[1].setOrigin(0.5, size / 2);
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


	bool showOrbits;
	bool copied = false;
	int savedTimeSpeed;
	sf::Vector2f cursorPosition;
	CenterOfGravity centerOfGravity;
	FpsTracker fpsTracker;
	BackGround* backGround;
	Timer timer;
	Physics physics;

	friend int Console::handleCommand(std::string command);
	Console console;

	sf::RenderWindow app;
	sf::View camera;
	sf::Time ellapsedTime;
	sf::Clock clock;

	std::vector<Object*> forGravityCenter;
	std::vector<Object> objects;

	Object* selectedObj;
	Object newObj;
	Object copiedObject;


private:

	void loadSettings();
	void saveSettings();
	void updateGui();
	void updateEvents();
	void updateGraphics();
	void updateObjects();
	void update();

};

