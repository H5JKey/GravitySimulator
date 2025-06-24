#pragma once
#include "SFML/Graphics.hpp"
#include "ParticleSources.hpp"


class ParticlesSystem {
public:

    static void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
    static void add(ParticleSource* source);
    static void update(sf::Time elapsed, float timeSpeed=1);
    static void clear();
    static void setOrbitLifeTime(sf::Time newLifeTime);
    static sf::Time getOrbitLifeTime();

private:
    static std::vector<ParticleSource*> m_sources;
    static sf::Time orbitLifeTime;
};






