#include "ParticlesSystem.h"
#include <iostream>


void ParticlesSystem::draw(sf::RenderTarget& target, sf::RenderStates states) {
    for (auto& source : m_sources) {
        source->draw(target, states);
    }
}

void ParticlesSystem::add(ParticleSource* source) {
    m_sources.push_back(source);
}

void ParticlesSystem::update(sf::Time elapsed) {
    for (auto& source : m_sources) {
        source->update(elapsed);
    }
}

std::vector<ParticleSource*> ParticlesSystem::m_sources(0);