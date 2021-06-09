#include <SFML/Graphics.hpp>
enum ParticleType {EMPTY, SAND, WATER, WOOD, FIRE};
enum ParticleColor {YELLOW, BLUE, BLACK, BROWN, RED};

class Particle {
    public:
        ParticleType pType;  // type of particle
        ParticleColor color; // color for particle to be drawn as
        uint32_t moveRange;  // range that particle can move in 1 frame
        int32_t lifeTime;   // time particle will live in frames (-1 for inf)
        bool hasBeenUpdated; // true if particle has been updated this frame

        Particle();
        Particle(ParticleType t);
        void setType(ParticleType t);
};