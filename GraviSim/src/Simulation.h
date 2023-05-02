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

	sf::RenderWindow app;
	sf::View camera;
	sf::Time ellapsedTime;
	sf::Clock clock, delta;
	sf::Vector2f offset; //camera offset
	Object* selectedObj;
	Object newObj;

	int savedTimeSpeed;

	struct FpsTracker : sf::Drawable{
	private:
		sf::Font font;
		sf::Text str;
	public:
		bool show;
		FpsTracker() {
			show = false;
			font.loadFromFile("C:/Windows/Fonts/arial.ttf");
			str.setFont(font);
			str.setCharacterSize(13);
			str.setStyle(sf::Text::Bold);
			str.setFillColor(sf::Color::White);
			str.setPosition(10, 7);
		}

		void calculate(sf::Time ellapsedTime) {
			str.setString(std::to_string(int(1 / ellapsedTime.asSeconds())));
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const {
			target.draw(str);
		}
	};

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
			size = 16;
			cross[0].setFillColor(sf::Color::Red);
			cross[1].setFillColor(sf::Color::Red);
			cross[0].setSize({ size, 1 });
			cross[1].setSize({ 1, size });
			cross[0].setOrigin(size/2, 0.5);
			cross[1].setOrigin(0.5, size/2);
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
	FpsTracker fpsTracker;
	BackGround* backGround;

	bool showOrbits;

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

