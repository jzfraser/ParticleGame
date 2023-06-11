#pragma once
#include <SFML/System.hpp>

const uint32_t WIN_WIDTH       = 1200;
const uint32_t WIN_HEIGHT      = 900;
const uint32_t WORLD_WIDTH     = 1200;
const uint32_t WORLD_HEIGHT    = 900;
const uint32_t PARTICLE_WIDTH  = WIN_WIDTH / WORLD_WIDTH;
const uint32_t PARTICLE_HEIGHT = WIN_HEIGHT / WORLD_HEIGHT;

const float GRAVITY = 10.f;

enum ParticleType { EMPTY, SAND, WATER, WOOD, FIRE };
