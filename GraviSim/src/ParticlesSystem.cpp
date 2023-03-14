#include "ParticlesSystem.h"


void ParticlesSystem::draw(sf::RenderTarget& target, sf::RenderStates states) {
    for (auto& source : m_sources) {
        source->draw(target, states);
    }
}

void ParticlesSystem::add(ParticleSource* source) {
    m_sources.push_back(source);
}

void ParticlesSystem::update(sf::Time elapsed, float timeSpeed) {
    for (int i = 0; i < m_sources.size(); ++i) {
        m_sources[i]->update(elapsed, timeSpeed);
        if (!m_sources[i]->inProcess) {
            delete(m_sources[i]);
            m_sources.erase(m_sources.begin() + i);
            
        }
    }
}

std::vector<ParticleSource*> ParticlesSystem::m_sources(0);