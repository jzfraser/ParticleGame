#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Particle.hpp"

class Grid {
    public:
        const uint32_t size;
        Particle** grid;

        Grid(uint32_t _size);
        ~Grid();
        void fill(ParticleType t);
        void check();
        bool slotIsEmpty(uint32_t row, uint32_t col);
        bool slotContains(ParticleType t, uint32_t row, uint32_t col);
        void moveFromTo(uint32_t fRow, uint32_t fCol, uint32_t tRow, uint32_t tCol);
        void copyFromTo(uint32_t fRow, uint32_t fCol, uint32_t tRow, uint32_t tCol);
    
    private:
        void updateSand(uint32_t row, uint32_t col);
        void updateWater(uint32_t row, uint32_t col);
        void updateWood(uint32_t row, uint32_t col);
        void updateFire(uint32_t row, uint32_t col);
};