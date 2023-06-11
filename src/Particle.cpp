#include "Particle.hpp"

Particle::Particle(ParticleType t) {
    pType          = t;
    hasBeenUpdated = false;
    setType(pType);
}

Particle::Particle() {
    pType          = EMPTY;
    hasBeenUpdated = false;
    lifeTime       = -1;
}

void Particle::setType(ParticleType t) {
    pType = t;
    switch (t) {
    case SAND:
        lifeTime = -1;
        break;
    case WATER:
        lifeTime = -1;
        break;
    case WOOD:
        lifeTime = -1;
        break;
    case FIRE:
        lifeTime = 20;
        break;
    case EMPTY:
    default:
        lifeTime = -1;
        break;
    }
}
