#pragma once
#include "SFML/Graphics.hpp"
#include "ParticleSources.h"
#include <iostream>


class ParticlesSystem {
public:
    static sf::Time orbitLifeTime;

    static void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
    static void add(ParticleSource* source);
    static void update(sf::Time elapsed, float timeSpeed);
    static void clear();

private:
    static std::vector<ParticleSource*> m_sources;
};






