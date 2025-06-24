#include "ParticlesSystem.hpp"



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

void ParticlesSystem::clear() {
    m_sources.clear();
}

void ParticlesSystem::setOrbitLifeTime(sf::Time newLifeTime) {
    orbitLifeTime = newLifeTime;

}

sf::Time ParticlesSystem::getOrbitLifeTime() {
    return orbitLifeTime;
}



std::vector<ParticleSource*> ParticlesSystem::m_sources(0);
sf::Time ParticlesSystem::orbitLifeTime = sf::milliseconds(5000);