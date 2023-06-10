#pragma once
#include <SFML/System.hpp>

const uint32_t WIN_WIDTH       = 800;
const uint32_t WIN_HEIGHT      = 600;
const uint32_t WORLD_SIZE      = 100;
const uint32_t PARTICLE_WIDTH  = WIN_WIDTH / WORLD_SIZE;
const uint32_t PARTICLE_HEIGHT = WIN_HEIGHT / WORLD_SIZE;

enum ParticleType { EMPTY, SAND, WATER, WOOD, FIRE };
enum ParticleColor { YELLOW, BLUE, BLACK, BROWN, RED };
