#pragma once
#include <SFML/System.hpp>

const uint32_t WIN_WIDTH       = 800;
const uint32_t WIN_HEIGHT      = 600;
const uint32_t WORLD_WIDTH     = 100;
const uint32_t WORLD_HEIGHT    = 100;
const uint32_t PARTICLE_WIDTH  = WIN_WIDTH / WORLD_WIDTH;
const uint32_t PARTICLE_HEIGHT = WIN_HEIGHT / WORLD_HEIGHT;

enum ParticleType { EMPTY, SAND, WATER, WOOD, FIRE };
enum ParticleColor { YELLOW, BLUE, BLACK, BROWN, RED };
