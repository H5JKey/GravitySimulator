#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class ParticleSource : public sf::Drawable, public sf::Transformable {
public:

    virtual void update(sf::Time elapsed, float timeSpeed = 1) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;


    ParticleSource(unsigned int count, sf::Vector2f position, sf::Vector3f color) :
        m_particles(count),
        m_vertices(sf::Points, count),
        m_emitter(position)
    {
        for (std::size_t i = 0; i < m_particles.size(); ++i) {
            m_vertices[i].color.r = static_cast<sf::Uint8>(color.x * 255);
            m_vertices[i].color.g = static_cast<sf::Uint8>(color.y * 255);
            m_vertices[i].color.b = static_cast<sf::Uint8>(color.z * 255);
        }
        inProcess = true;
    }



protected:

    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lefttime, lifetime;
    };

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Vector2f m_emitter;
public:
    bool inProcess;
};

class Explosion : public ParticleSource
{
public:
    Explosion(unsigned int count, sf::Vector2f position, sf::Vector3f color) : ParticleSource(count, position, color)
    {
        for (int i = 0; i < m_particles.size(); i++) {
            set(i);
        }
    }

    virtual void update(sf::Time elapsed, float timeSpeed)
    {
        bool flag = true;
        for (std::size_t i = 0; i < m_particles.size(); ++i)
        {
            Particle& p = m_particles[i];
            p.lefttime -= elapsed * timeSpeed;

            if (p.lefttime <= sf::Time::Zero) {
                continue;
            }
            else flag = false;

            m_vertices[i].position += p.velocity * elapsed.asSeconds() * timeSpeed;

            float ratio = p.lefttime.asSeconds() / p.lifetime.asSeconds();
            m_vertices[i].color.a = static_cast<sf::Uint8>(0.5 * ratio * 255);
        }
        if (flag)
            inProcess = false;
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const
    {
        states.transform *= getTransform();

        states.texture = NULL;

        target.draw(m_vertices, states);
    }



    virtual void set(std::size_t index)
    {
        float angle = (std::rand() % 360) * 3.14f / 180.f;
        float speed = (std::rand() % 70) + 50.f;
        m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        m_particles[index].lifetime = sf::milliseconds((std::rand() % 1000) + 700);
        m_particles[index].lefttime = m_particles[index].lifetime;
        m_vertices[index].position = m_emitter;
    }

};

class Pixel : public ParticleSource {
public:
    Pixel(sf::Vector2f position, sf::Vector3f color, sf::Time lifeTime) : ParticleSource(1, position, color)
    {
        m_particles[0].lifetime = lifeTime;
        m_particles[0].lefttime = m_particles[0].lifetime;
        m_vertices[0].position = m_emitter;
    }

    virtual void update(sf::Time elapsed, float timeSpeed)
    {
        bool flag = true;

        Particle& p = m_particles[0];
        p.lefttime -= elapsed * timeSpeed;

        if (p.lefttime <= sf::Time::Zero)
            inProcess = false;

        float ratio = p.lefttime.asSeconds() / p.lifetime.asSeconds();
        m_vertices[0].color.a = static_cast<sf::Uint8>(0.5 * ratio * 255);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const
    {
        states.transform *= getTransform();

        states.texture = NULL;

        target.draw(m_vertices, states);
    }



};
