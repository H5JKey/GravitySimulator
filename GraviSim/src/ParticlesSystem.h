#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class ParticleSource: public sf::Drawable, public sf::Transformable {
public:
    virtual void update(sf::Time elapsed, float timeSpeed=1) = 0;
    virtual void setEmitter(sf::Vector2f position) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual void resetParticle(std::size_t index) = 0;
    

    ParticleSource(unsigned int count, sf::Vector2f position, sf::Vector3f color) : 
        m_particles(count),
        m_vertices(sf::Points, count),
        m_lifetime(sf::seconds(2.f)),
        m_emitter(position)
        {
            for (std::size_t i = 0; i < m_particles.size(); ++i) {
                m_vertices[i].color.r = static_cast<sf::Uint8>(color.x*255);
                m_vertices[i].color.g = static_cast<sf::Uint8>(color.y*255);
                m_vertices[i].color.b = static_cast<sf::Uint8>(color.z*255);
            }
            inProcess = true;
        }
protected:

    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
public:
    bool inProcess;
};

class Explosion :  public ParticleSource
{
public:
        Explosion(unsigned int count, sf::Vector2f position, sf::Vector3f color) : ParticleSource(count,position, color)
        {
            for (int i = 0; i < m_particles.size(); i++) {
                resetParticle(i);
            }
        }

        virtual void setEmitter(sf::Vector2f position)
        {
            m_emitter = position;
            for (int i = 0; i < m_particles.size(); i++) {
                resetParticle(i);
            }
        }

        virtual void update(sf::Time elapsed, float timeSpeed)
        {
            bool flag = true;
            for (std::size_t i = 0; i < m_particles.size(); ++i)
            {
                // update the particle lifetime
                Particle& p = m_particles[i];
                p.lifetime -= elapsed*timeSpeed;

                // if the particle is dead, respawn it
                if (p.lifetime <= sf::Time::Zero) {
                    continue;
                }
                else flag = false;

            // update the position of the corresponding vertex
                m_vertices[i].position += p.velocity * elapsed.asSeconds()*timeSpeed;

                // update the alpha (transparency) of the particle according to its lifetime
                float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
                m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
            }
            if (flag)
                inProcess = false;
        }

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states=sf::RenderStates::Default) const
        {
            // apply the transform
            states.transform *= getTransform();

            // our particles don't use a texture
            states.texture = NULL;

            // draw the vertex array
            target.draw(m_vertices, states);
        }



        virtual void resetParticle(std::size_t index)
        {
            // give a random velocity and lifetime to the particle
            float angle = (std::rand() % 360) * 3.14f / 180.f;
            float speed = (std::rand() % 70) + 50.f;
            m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
            m_particles[index].lifetime = sf::milliseconds((std::rand() % 1000) + 700);

            // reset the position of the corresponding vertex
            m_vertices[index].position = m_emitter;
        }

};




class ParticlesSystem {
public:
    static void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);


    static void add(ParticleSource* source);

    static void update(sf::Time elapsed, float timeSpeed);

private:
    static std::vector<ParticleSource*> m_sources;
};


