#include <SFML/Graphics.hpp>
#include "Simulation.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow App(sf::VideoMode(), "Gravity Simulator",sf::Style::Fullscreen,settings);

    sf::Clock clock;
    clock.restart();

    Simulation::bodies.push_back(SimpleBody(150000, sf::Vector2f(App.getSize().x / 2, App.getSize().y / 2), sf::Vector2f(0, 0)));
    Simulation::bodies.push_back(SimpleBody(1000, sf::Vector2f(App.getSize().x / 2, App.getSize().y / 2-250),sf::Vector2f(400,0)));
    Simulation::bodies.push_back(SimpleBody(100, sf::Vector2f(App.getSize().x / 2, App.getSize().y / 2 + 450), sf::Vector2f(-500, 0)));
    Simulation::bodies.push_back(SimpleBody(0.001, sf::Vector2f(App.getSize().x / 2-90, App.getSize().y / 2 - 270), sf::Vector2f(450, 0)));


    while (App.isOpen())
    {
        sf::Event event;
        (App.pollEvent(event));
        // Close window : exit
        if (event.type == sf::Event::Closed)
            App.close();

        // Escape key : exit
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
            App.close()
            ;
        float EllapsedTime = clock.getElapsedTime().asSeconds();
        clock.restart();

        Simulation::update(EllapsedTime);

        App.clear();
        for (auto &body : Simulation::bodies) {
             App.draw(body.GetDrawing());
        }
        App.display();
    }

    return 0;
}