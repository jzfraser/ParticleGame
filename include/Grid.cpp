#include "Grid.hpp"
#include <iostream>

Grid::Grid(uint32_t _size) : size(_size) {
    grid = new Particle*[size];
    for (int row = 0; row < size; row++) {
        grid[row] = new Particle[size];
    }
    fill(EMPTY);
}

Grid::~Grid() {
    for (int row = 0; row < size; row++) {
        delete[] grid[row];
    }
    delete[] grid;
}

void Grid::fill(ParticleType t) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            grid[row][col].setType(t);
        }
    }
}

void Grid::check() {
    for (int row = size - 1; row >= 0; row--) {
        for (int col = 0; col < size; col++) {
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
                // std::cout << row << " " << col << " Empty\n";
                break;
            default:
                std::cout << "check hit default\n";
                break;
            }
        }
    }
}

bool Grid::slotIsEmpty(uint32_t row, uint32_t col) {
    return slotContains(EMPTY, row, col);
}


bool Grid::slotContains(ParticleType t, uint32_t row, uint32_t col) {
    return grid[row][col].pType == t;
}

void Grid::moveFromTo(uint32_t fRow, uint32_t fCol, uint32_t tRow, uint32_t tCol) {
    ParticleType oldType = grid[tRow][tCol].pType;
    grid[tRow][tCol].setType(grid[fRow][fCol].pType);
    grid[fRow][fCol].setType(oldType);
    // grid[fRow][fCol].setType(EMPTY);
    grid[fRow][fCol].hasBeenUpdated = true;
    grid[tRow][tCol].hasBeenUpdated = true;
}

void Grid::copyFromTo(uint32_t fRow, uint32_t fCol, uint32_t tRow, uint32_t tCol) {
    grid[tRow][tCol].setType(grid[fRow][fCol].pType);
    grid[fRow][fCol].hasBeenUpdated = true;
    grid[tRow][tCol].hasBeenUpdated = true;
}

void Grid::updateSand(uint32_t row, uint32_t col) {
    if (grid[row][col].hasBeenUpdated) {
        grid[row][col].hasBeenUpdated = false;
        return;
    }
    if (row < size - 1) {
        if (slotIsEmpty(row + 1, col) || slotContains(WATER, row + 1, col)) {
            moveFromTo(row, col, row + 1, col);
        } else if (col > 0 &&
        (slotIsEmpty(row + 1, col - 1) || slotContains(WATER, row + 1, col - 1))) {
            moveFromTo(row, col, row + 1, col - 1);
        } else if (col < size - 1 &&
        (slotIsEmpty(row + 1, col + 1) || slotContains(WATER, row + 1, col + 1))) {
            moveFromTo(row, col, row + 1, col + 1);
        }
    }
    // std::cout << row << " " << col << " Sand found!\n";
}

void Grid::updateWater(uint32_t row, uint32_t col) {
    if (grid[row][col].hasBeenUpdated) {
        grid[row][col].hasBeenUpdated = false;
        return;
    }
    if (row < size - 1) {
        if (slotIsEmpty(row + 1, col)) {
            moveFromTo(row, col, row + 1, col);
        } else if (col > 0 && slotIsEmpty(row + 1, col - 1)) {
            moveFromTo(row, col, row + 1, col - 1);
        } else if (col < size - 1 && slotIsEmpty(row + 1, col + 1)) {
            moveFromTo(row, col, row + 1, col + 1);
        } else if (col > 0 && slotIsEmpty(row, col - 1)) {
            moveFromTo(row, col, row, col - 1);
        } else if (col < size - 1 && slotIsEmpty(row, col + 1)) {
            moveFromTo(row, col, row, col + 1);
        }
    } else {
        if (col > 0 && slotIsEmpty(row, col - 1)) {
            moveFromTo(row, col, row, col - 1);
        } else if (col < size - 1 && slotIsEmpty(row, col + 1)) {
            moveFromTo(row, col, row, col + 1);
        }
    }
    // std::cout << row << " " << col << " Water found!\n";
}

void Grid::updateWood(uint32_t row, uint32_t col) {
    return;
}

void Grid::updateFire(uint32_t row, uint32_t col) {
    Particle* p = &grid[row][col];
    if (p->lifeTime == 0) {
        p->setType(EMPTY);
        return;
    }
    if (p->hasBeenUpdated) {
        p->hasBeenUpdated = false;
        return;
    }
    if (row > 0 && row < size - 1) {
        if (slotContains(WOOD, row + 1, col)) {
            copyFromTo(row, col, row + 1, col);
        }
        if (col > 0 && slotContains(WOOD, row + 1, col - 1)) {
            copyFromTo(row, col, row + 1, col - 1);
        }
        if (col < size - 1 && slotContains(WOOD, row + 1, col + 1)) {
            copyFromTo(row, col, row + 1, col + 1);
        }
    }
    if (row < size - 1) {
        if (col > 0 && slotContains(WOOD, row - 1, col - 1)) {
            copyFromTo(row, col, row - 1, col - 1);
        }
        if (col < size - 1 && slotContains(WOOD, row - 1, col + 1)) {
            copyFromTo(row, col, row - 1, col + 1);
        }
    }
    if (col > 0 && slotContains(WOOD, row, col - 1)) {
        copyFromTo(row, col, row, col - 1);
    }
    if (col < size - 1 && slotContains(WOOD, row, col + 1)) {
        copyFromTo(row, col, row, col + 1);
    }
    if (!p->hasBeenUpdated && p->lifeTime == 0) {
        grid[row][col].setType(EMPTY);
    }
    if (p->lifeTime > 0) {
        p->lifeTime--;
    }
}
