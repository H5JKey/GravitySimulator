#include <SFML/Graphics.hpp>
#include "Simulation.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow App(sf::VideoMode(800, 600), "Gravity Simulator",sf::Style::Default,settings);

    sf::Clock clock;
    clock.restart();

    Simulation::bodies.push_back(SimpleBody(100, sf::Vector2f(50, 50),sf::Vector2f(20,0)));
    while (App.isOpen())
    {
        clock.restart();
        float EllapsedTime = clock.getElapsedTime().asSeconds();
        Simulation::update(EllapsedTime*1000);

        App.clear();
        for (auto &body : Simulation::bodies) {
             App.draw(body.GetDrawing());
        }
        App.display();
    }

    return 0;
}