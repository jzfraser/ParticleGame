# ParticleGame

#### Author: Jack Fraser

This is a simple particle simulator using cellular automata like in _The Game of Life_.
It is a work in progress, but already shows off a few different particle types that have some
basic rules they follow. Not meant to be a full functioning simulator, but rather a way for me
to learn more C++ and SFML.

### Keybinds

- c : clear all particles

### Prerequisites

- C++, C/C++ compiler, cmake, SFML

### How to build/run

Here are the steps I go through to build/run this easily

1. Clone the repo locally
2. cd into the ParticleGame directory
3. copy and rename CMakeLists_default.txt or CMakeLists_macos.txt to CMakeLists.txt depending on platform
4. run `mkdir build` and cd into the build directory
5. run `cmake ..` which will create and put all build files into the build directory based on the CMakeLists.txt in the root directory
6. run `make` inside the build directory to create the executable
7. run `./ParticleGame` in the build directory to start up the game!

### Current Particles:

- Sand: Falls down and spreads out
- Water: Flows down and to the sides
- Wood: Stationary and flammable
- Fire: Burns up flammable particles nearby

### Upcoming Additions (maybe):

- Pausing and playing physics
- Ability to erase particles
- Hopefully slightly better visuals
- Smoke particle
- Acid particle
