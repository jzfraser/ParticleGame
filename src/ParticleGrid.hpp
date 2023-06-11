#include "Constants.hpp"
#include "Particle.hpp"
#include <SFML/Graphics.hpp>

class ParticleGrid : public sf::Drawable, public sf::Transformable {
public:
    Particle** grid;

    ParticleGrid(uint16_t _width, uint16_t _height);
    ~ParticleGrid();
    void update();
    void createP(ParticleType t, uint16_t row, uint16_t col);

private:
    const uint16_t width;
    const uint16_t height;
    sf::VertexArray particles;
    uint16_t numParticles;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void fillGrid(ParticleType t);
    bool isEmpty(uint16_t row, uint16_t col);
    bool containsType(ParticleType t, uint16_t row, uint16_t col);
    void moveFromTo(uint16_t fRow, uint16_t fCol, uint16_t tRow, uint16_t tCol);
    void copyFromTo(uint16_t fRow, uint16_t fCol, uint16_t tRow, uint16_t tCol);
    void updateSand(uint16_t row, uint16_t col, uint16_t pIndex);
    void updateWater(uint16_t row, uint16_t col, uint16_t pIndex);
    void updateWood(uint16_t row, uint16_t col, uint16_t pIndex);
    void updateFire(uint16_t row, uint16_t col, uint16_t pIndex);
};
