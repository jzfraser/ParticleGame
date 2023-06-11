#include "ParticleGrid.hpp"

ParticleGrid::ParticleGrid(uint16_t _width, uint16_t _height)
: width(_width), height(_height), particles(sf::Quads, width * height * 4), numParticles(0) {
    grid = new Particle*[height];
    for (uint16_t row = 0; row < height; row++) {
        grid[row] = new Particle[width];
    }
    fillGrid(EMPTY);
}

ParticleGrid::~ParticleGrid() {
    for (uint16_t row = 0; row < height; row++) {
        delete[] grid[row];
    }
    delete[] grid;
}

void ParticleGrid::update() {
    particles.clear();
    particles.resize(numParticles * 4);
    uint16_t pIndex = 0;
    for (int16_t row = height - 1; row >= 0; row--) {
        for (uint16_t col = 0; col < width; col++) {
            switch (grid[row][col].pType) {
            case SAND:
                updateSand(row, col, pIndex);
                pIndex++;
                break;
            case WATER:
                updateWater(row, col, pIndex);
                pIndex++;
                break;
            case WOOD:
                updateWood(row, col, pIndex);
                pIndex++;
                break;
            case FIRE:
                updateFire(row, col, pIndex);
                pIndex++;
                break;
            case EMPTY:
            default:
                break;
            }
        }
    }
}

void ParticleGrid::createP(ParticleType t, uint16_t row, uint16_t col) {
    if (isEmpty(row, col)) {
        grid[row][col].setType(t);
        numParticles++;
    }
}


void ParticleGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = NULL;
    target.draw(particles, states);
}

void ParticleGrid::fillGrid(ParticleType t) {
    for (uint16_t row = 0; row < height; row++) {
        for (uint16_t col = 0; col < width; col++) {
            grid[row][col].setType(t);
        }
    }
}

bool ParticleGrid::isEmpty(uint16_t row, uint16_t col) {
    return containsType(EMPTY, row, col);
}

bool ParticleGrid::containsType(ParticleType t, uint16_t row, uint16_t col) {
    return grid[row][col].pType == t;
}

void ParticleGrid::moveFromTo(uint16_t fRow, uint16_t fCol, uint16_t tRow, uint16_t tCol) {
    ParticleType temp = grid[tRow][tCol].pType;
    grid[tRow][tCol].setType(grid[fRow][fCol].pType);
    grid[fRow][fCol].setType(temp);
    grid[fRow][fCol].hasBeenUpdated = true;
    grid[tRow][tCol].hasBeenUpdated = true;
}

void ParticleGrid::copyFromTo(uint16_t fRow, uint16_t fCol, uint16_t tRow, uint16_t tCol) {
    grid[tRow][tCol].setType(grid[fRow][fCol].pType);
    grid[fRow][fCol].hasBeenUpdated = true;
    grid[tRow][tCol].hasBeenUpdated = true;
}

void ParticleGrid::updateSand(uint16_t row, uint16_t col, uint16_t pIndex) {
    sf::Vertex* p = &particles[pIndex * 4];
    for (uint8_t i = 0; i < 4; i++) {
        p[i].color = sf::Color(210, 180, 140);
    }
    if (grid[row][col].hasBeenUpdated) {
        grid[row][col].hasBeenUpdated = false;
        return;
    }
    if (row < height - 1) {
        if (isEmpty(row + 1, col) || containsType(WATER, row + 1, col)) {
            moveFromTo(row, col, row + 1, col);
            p[0].position = sf::Vector2f(col * PARTICLE_HEIGHT, (row + 1) * PARTICLE_HEIGHT);
            p[1].position = sf::Vector2f(col * PARTICLE_HEIGHT, (row + 1 + 1) * PARTICLE_HEIGHT);
            p[2].position = sf::Vector2f(
                (col + 1) * PARTICLE_HEIGHT, (row + 1 + 1) * PARTICLE_HEIGHT);
            p[3].position = sf::Vector2f((col + 1) * PARTICLE_HEIGHT, (row + 1) * PARTICLE_HEIGHT);
        } else if (col > 0 &&
            (isEmpty(row + 1, col - 1) || containsType(WATER, row + 1, col - 1))) {
            moveFromTo(row, col, row + 1, col - 1);
            p[0].position = sf::Vector2f((col - 1) * PARTICLE_HEIGHT, (row + 1) * PARTICLE_HEIGHT);
            p[1].position = sf::Vector2f(
                (col - 1) * PARTICLE_HEIGHT, (row + 1 + 1) * PARTICLE_HEIGHT);
            p[2].position = sf::Vector2f((col - 1 + 1) * PARTICLE_HEIGHT,
                (row + 1 + 1) * PARTICLE_HEIGHT);
            p[3].position = sf::Vector2f(
                (col - 1 + 1) * PARTICLE_HEIGHT, (row + 1) * PARTICLE_HEIGHT);
        } else if (col < width - 1 &&
            (isEmpty(row + 1, col + 1) || containsType(WATER, row + 1, col + 1))) {
            moveFromTo(row, col, row + 1, col + 1);
            p[0].position = sf::Vector2f((col + 1) * PARTICLE_HEIGHT, (row + 1) * PARTICLE_HEIGHT);
            p[1].position = sf::Vector2f(
                (col + 1) * PARTICLE_HEIGHT, (row + 1 + 1) * PARTICLE_HEIGHT);
            p[2].position = sf::Vector2f((col + 1 + 1) * PARTICLE_HEIGHT,
                (row + 1 + 1) * PARTICLE_HEIGHT);
            p[3].position = sf::Vector2f(
                (col + 1 + 1) * PARTICLE_HEIGHT, (row + 1) * PARTICLE_HEIGHT);
        } else {
            p[0].position = sf::Vector2f(col * PARTICLE_HEIGHT, row * PARTICLE_HEIGHT);
            p[1].position = sf::Vector2f(col * PARTICLE_HEIGHT, (row + 1) * PARTICLE_HEIGHT);
            p[2].position = sf::Vector2f((col + 1) * PARTICLE_HEIGHT, (row + 1) * PARTICLE_HEIGHT);
            p[3].position = sf::Vector2f((col + 1) * PARTICLE_HEIGHT, row * PARTICLE_HEIGHT);
        }
    }
}

void ParticleGrid::updateWater(uint16_t row, uint16_t col, uint16_t pIndex) {
}

void ParticleGrid::updateWood(uint16_t row, uint16_t col, uint16_t pIndex) {
}

void ParticleGrid::updateFire(uint16_t row, uint16_t col, uint16_t pIndex) {
}
