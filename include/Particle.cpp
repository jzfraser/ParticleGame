#include "Particle.hpp"

Particle::Particle(ParticleType t) {
    pType = t;
    hasBeenUpdated = false;
    setType(pType);
}

Particle::Particle() {
    pType = EMPTY;
    color = BLACK;
    hasBeenUpdated = false;
    moveRange = 0;
    lifeTime = -1;
}

void Particle::setType(ParticleType t) {
    pType = t;
    switch (t) {
        case SAND:
            color = YELLOW;
            moveRange = 1;
            lifeTime = -1;
            break;
        case WATER:
            color = BLUE;
            moveRange = 2;
            lifeTime = -1;
            break;
        case WOOD:
            color = BROWN;
            moveRange = 0;
            lifeTime = -1;
            break;
        case FIRE:
            color = RED;
            moveRange = 1;
            lifeTime = 20;
            break;
        case EMPTY:
        default:
            color = BLACK;
            moveRange = 0;
            lifeTime = -1;
            break;
    }
}