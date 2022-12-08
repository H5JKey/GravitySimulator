#include <SFML/Graphics.hpp>
#include "Simulation.h"
#include "SimpleBody.h"
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
    float size = 1;

    bool flag = false;
    sf::Vector2f Pos;

    sf::View camera;
    camera.reset(sf::FloatRect(0, 0, App.getSize().x, App.getSize().y));

    camera.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    SimpleBody* selectedObj = nullptr;

    bool stop = false;

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
            if (event.mouseWheel.delta > 0)
                camera.zoom(1.1);
            else 
                camera.zoom(0.9);
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (selectedObj == nullptr) {
                auto mb = sf::Mouse::getPosition();
                for (auto& body : Simulation::bodies) {
                    if (body.GetDrawing().getGlobalBounds().contains(App.mapPixelToCoords(mb))) {
                        selectedObj = &body;
                        break;
                    }
                }
            }
        }

        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::BackSpace))
            stop = !stop;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

            sf::Vector2f CurrentmousePos = sf::Vector2f(sf::Mouse::getPosition() + App.getPosition());

            offset = (CurrentmousePos - Pos) * float(0.7);
            Pos = sf::Vector2f(sf::Mouse::getPosition() + App.getPosition());
        }
        else {
            Pos = sf::Vector2f(sf::Mouse::getPosition() + App.getPosition());
        }

        camera.move(-offset);


        float EllapsedTime = clock.getElapsedTime().asSeconds();
        clock.restart();

        if (!stop) 
            Simulation::update(0.0002);     

        if (selectedObj != nullptr)
            camera.setCenter(selectedObj->pos);

        App.clear();
        for (auto &body : Simulation::bodies) {
             App.draw(body.GetDrawing());
        }

        App.setView(camera);
        App.display();
    }

    return 0;
}