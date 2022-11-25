#include <SFML/Graphics.hpp>
#include "Simulation.h"
#include <ppl.h>
#include <iostream>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow App(sf::VideoMode(), "Gravity Simulator",sf::Style::Fullscreen,settings);

    sf::Clock clock;
    clock.restart();

    Simulation::bodies.push_back(SimpleBody(10000, sf::Vector2f(App.getSize().x / 2, App.getSize().y / 2), sf::Vector2f(0, 0)));
    Simulation::bodies.push_back(SimpleBody(100, sf::Vector2f(App.getSize().x / 2, App.getSize().y / 2-500), sf::Vector2f(120, 0)));
    Simulation::bodies.push_back(SimpleBody(0.001, sf::Vector2f(App.getSize().x / 2-10, App.getSize().y / 2 - 510), sf::Vector2f(185, 0)));

    sf::Vector2f offset = sf::Vector2f(0, 0);
    float size = 10;

    bool flag = false;
    sf::Vector2f Pos;


    while (App.isOpen())
    {
        sf::Event event;
        (App.pollEvent(event));
        // Close window : exit
        if (event.type == sf::Event::Closed)
            App.close();

        // Escape key : exit
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
            App.close();


        if (event.type==sf::Event::MouseWheelMoved) {
            size+=event.mouseWheel.delta;
        }


        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

            sf::Vector2f CurrentmousePos = sf::Vector2f(sf::Mouse::getPosition() + App.getPosition());
            /*
            if (CurrentmousePos.x == 0) offset.x -= 0.05;
            if (CurrentmousePos.x == App.getSize().x - 1) offset.x += 0.05;
            if (CurrentmousePos.y == 0) offset.y -= 0.05;
            if (CurrentmousePos.y == App.getSize().y - 1) offset.y += 0.05;
            */

            offset += (CurrentmousePos - Pos) * float(0.7);
            Pos = sf::Vector2f(sf::Mouse::getPosition() + App.getPosition());
        }
        else {
            Pos = sf::Vector2f(sf::Mouse::getPosition() + App.getPosition());
        }

        float EllapsedTime = clock.getElapsedTime().asSeconds();
        clock.restart();


        Simulation::update(EllapsedTime);

        App.clear();
        for (auto &body : Simulation::bodies) {
             App.draw(body.GetDrawing(offset,size));
        }
        App.display();
    }

    return 0;
}