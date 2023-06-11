#include "Constants.hpp"
#include <SFML/Graphics.hpp>

class Particle {
    public:
    ParticleType pType;  // type of particle
    int8_t lifeTime;     // time particle will live in frames (-1 for inf)
    bool hasBeenUpdated; // true if particle has been updated this frame

    Particle();
    Particle(ParticleType t);
    void setType(ParticleType t);
};
