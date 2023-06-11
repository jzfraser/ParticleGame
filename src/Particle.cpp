#include "Particle.hpp"

Particle::Particle(ParticleType t) {
    pType          = t;
    hasBeenUpdated = false;
    velocity       = sf::Vector2i(0, 0);
    setType(pType);
}

Particle::Particle() {
    pType          = EMPTY;
    hasBeenUpdated = false;
    velocity       = sf::Vector2i(0, 0);
    setType(pType);
}

void Particle::setType(ParticleType t) {
    pType = t;
    switch (t) {
    case SAND:
        lifeTime = 0;
        break;
    case WATER:
        lifeTime = 0;
        break;
    case WOOD:
        lifeTime = 0;
        break;
    case FIRE:
        lifeTime = 20;
        break;
    case EMPTY:
    default:
        lifeTime = 0;
        break;
    }
}
