#include "ParticleGrid.hpp"
#include "Constants.hpp"
#include <algorithm>
#include <iostream>

ParticleGrid::ParticleGrid(uint16_t _width, uint16_t _height)
: width(_width),
  height(_height),
  particles(sf::Quads, width * height * 4),
  dt(0),
  updateDirection(1) {
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

void ParticleGrid::clearParticles() {
    for (int16_t row = height - 1; row >= 0; row--) {
        for (uint16_t col = 0; col < width; col++) {
            grid[row][col].setType(EMPTY);
        }
    }
}

void ParticleGrid::update(float _dt) {
    dt = _dt;
    for (int16_t row = height - 1; row >= 0; row--) {
        for (uint16_t col = updateDirection == 1 ? 0 : width - 1; col < width && col >= 0;
             updateDirection == 1 ? col++ : col--) {
            if (grid[row][col].hasBeenUpdated)
                continue;
            switch (grid[row][col].pType) {
            case SAND:
                updateSand(row, col);
                break;
            case WATER:
                updateWater(row, col);
                break;
            case WOOD:
                updateWood(row, col);
                break;
            case FIRE:
                updateFire(row, col);
                break;
            case EMPTY:
            default:
                break;
            }
        }
    }
    updateVertices();
    updateDirection *= -1;
}

void ParticleGrid::createP(ParticleType t, uint16_t row, uint16_t col) {
    if (row < 0 || row >= height)
        return;
    if (col < 0 || col >= width)
        return;
    if (isEmpty(row, col)) {
        grid[row][col].setType(t);
        grid[row][col].velocity = sf::Vector2f(0.0f, 1.0f);
    }
}

void ParticleGrid::readyParticles() {
    for (uint16_t r = 0; r < height; r++) {
        for (uint16_t c = 0; c < width; c++) {
            grid[r][c].hasBeenUpdated = false;
        }
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
    grid[tRow][tCol].setType(grid[fRow][fCol].pType);
    grid[tRow][tCol].velocity = grid[fRow][fCol].velocity;
    grid[fRow][fCol].setType(EMPTY);
    grid[tRow][tCol].hasBeenUpdated = true;
}

void ParticleGrid::copyFromTo(uint16_t fRow, uint16_t fCol, uint16_t tRow, uint16_t tCol) {
    grid[tRow][tCol].setType(grid[fRow][fCol].pType);
    grid[tRow][tCol].velocity       = grid[fRow][fCol].velocity;
    grid[tRow][tCol].hasBeenUpdated = true;
}

void ParticleGrid::updateVertices() {
    for (uint16_t r = 0; r < height; r++) {
        for (uint16_t c = 0; c < width; c++) {
            sf::Vertex* p = &particles[(r + c * height) * 4];
            p[0].position = sf::Vector2f(c * PARTICLE_WIDTH, r * PARTICLE_HEIGHT);
            p[1].position = sf::Vector2f(c * PARTICLE_WIDTH, (r + 1) * PARTICLE_HEIGHT);
            p[2].position = sf::Vector2f((c + 1) * PARTICLE_WIDTH, (r + 1) * PARTICLE_HEIGHT);
            p[3].position = sf::Vector2f((c + 1) * PARTICLE_WIDTH, r * PARTICLE_HEIGHT);

            switch (grid[r][c].pType) {
            case SAND:
                p[0].color = sf::Color(210, 180, 140);
                p[1].color = sf::Color(210, 180, 140);
                p[2].color = sf::Color(210, 180, 140);
                p[3].color = sf::Color(210, 180, 140);
                break;
            case WATER:
                p[0].color = sf::Color::Blue;
                p[1].color = sf::Color::Blue;
                p[2].color = sf::Color::Blue;
                p[3].color = sf::Color::Blue;
                break;
            case WOOD:
                p[0].color = sf::Color(56, 42, 32);
                p[1].color = sf::Color(56, 42, 32);
                p[2].color = sf::Color(56, 42, 32);
                p[3].color = sf::Color(56, 42, 32);
                break;
            case FIRE:
                p[0].color = sf::Color::Red;
                p[1].color = sf::Color::Red;
                p[2].color = sf::Color::Red;
                p[3].color = sf::Color::Red;
                break;
            case EMPTY:
            default:
                p[0].color = sf::Color::Black;
                p[1].color = sf::Color::Black;
                p[2].color = sf::Color::Black;
                p[3].color = sf::Color::Black;
            }
        }
    }
}

void ParticleGrid::updateSand(uint16_t row, uint16_t col) {
    Particle* p   = &grid[row][col];
    p->velocity.y = std::clamp(p->velocity.y + (dt * GRAVITY), -10.f, 10.f);
    int bound     = static_cast<int>(p->velocity.y);
    uint16_t r    = row;
    for (int dist = 1; dist <= bound; dist++) {
        if (r + dist < height) {
            if (isEmpty(r + dist, col)) {
                moveFromTo(r, col, r + dist, col);
                r += dist;
            } else {
                p->velocity = sf::Vector2f(0.f, 1.f);
                break;
            }
        }
    }
    if (!grid[r][col].hasBeenUpdated) {
        if (row + 1 < height) {
            if (col > 0 && isEmpty(row + 1, col - 1)) {
                moveFromTo(row, col, row + 1, col - 1);
            } else if (col < width && isEmpty(row + 1, col + 1)) {
                moveFromTo(row, col, row + 1, col + 1);
            }
        }
    }
}

void ParticleGrid::updateWater(uint16_t row, uint16_t col) {
    Particle* p   = &grid[row][col];
    p->velocity.y = std::clamp(p->velocity.y + (dt * GRAVITY), -10.f, 10.f);
    p->velocity.x = std::clamp(p->velocity.x + (dt * 5.f), -6.f, 6.f);

    int yBound = static_cast<int>(p->velocity.y);
    uint16_t r = row;
    for (int dist = 0; dist <= yBound; dist++) {
        if (r + dist < height) {
            if (isEmpty(r + dist, col)) {
                moveFromTo(r, col, r + dist, col);
                r += dist;
            }
        }
    }

    int direction = rand() % 2 == 0 ? 1 : -1;
    uint16_t c    = col;
    if (!grid[r][col].hasBeenUpdated) {
        if (row + 1 < height) {
            int move = 1 * direction;
            if (col + move >= 0 && col + move < width && (isEmpty(row + 1, col + move))) {
                moveFromTo(row, col, row + 1, col + move);
                c = col + move;
            } else {
                direction *= -1;
                move = 1 * direction;
                if (col + move >= 0 && col + move < width &&
                    (isEmpty(row + 1, col + move))) {
                    moveFromTo(row, col, row + 1, col + move);
                    c = col + move;
                }
            }
        }
    }
    if (!grid[row][c].hasBeenUpdated) {
        int xBound = static_cast<int>(p->velocity.x);
        c          = col;
        r          = row;
        for (int dist = 1; dist <= xBound; dist++) {
            int move = dist * direction;
            if (c + move >= 0 && c + move < width && isEmpty(r, c + move)) {
                if (r + 1 < height && isEmpty(r + 1, c + move)) {
                    moveFromTo(r, c, r + 1, c + move);
                    c += move;
                }
                moveFromTo(r, c, r, c + move);
                c += move;
            }
        }
    }
}

void ParticleGrid::updateWood(uint16_t row, uint16_t col) {
    return;
}

void ParticleGrid::updateFire(uint16_t row, uint16_t col) {
    Particle* p = &grid[row][col];
    if (p->hasBeenUpdated)
        return;
    if (!p->hasBeenUpdated && p->lifeTime == 0) {
        p->setType(EMPTY);
        return;
    }
    if (row < height - 1) {
        if (containsType(WOOD, row + 1, col)) {
            copyFromTo(row, col, row + 1, col);
        }
        if (col > 0 && containsType(WOOD, row + 1, col - 1)) {
            copyFromTo(row, col, row + 1, col - 1);
        }
        if (col < width - 1 && containsType(WOOD, row + 1, col + 1)) {
            copyFromTo(row, col, row + 1, col + 1);
        }
    }
    if (row > 0 && col < width - 1) {
        if (containsType(WOOD, row - 1, col)) {
            copyFromTo(row, col, row - 1, col);
        }
        if (col > 0 && containsType(WOOD, row - 1, col - 1)) {
            copyFromTo(row, col, row - 1, col - 1);
        }
        if (col < width - 1 && containsType(WOOD, row - 1, col + 1)) {
            copyFromTo(row, col, row - 1, col + 1);
        }
    }
    if (col > 0 && containsType(WOOD, row, col - 1)) {
        copyFromTo(row, col, row, col - 1);
    }
    if (col < width - 1 && containsType(WOOD, row, col + 1)) {
        copyFromTo(row, col, row, col + 1);
    }
    if (p->lifeTime > 0) {
        p->lifeTime--;
    }
}
