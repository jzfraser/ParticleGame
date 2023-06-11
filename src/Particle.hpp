#include "Constants.hpp"
#include <SFML/Graphics.hpp>

class Particle {
public:
    ParticleType pType; // type of particle
    sf::Vector2i velocity;
    uint8_t lifeTime; // time particle will live in frames (only used in fire)
    bool hasBeenUpdated; // true if particle has been updated this frame

    Particle();
    Particle(ParticleType t);
    void setType(ParticleType t);
};
