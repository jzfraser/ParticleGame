# ParticleGame

#### Author: Jack Fraser

This is a simple particle simulator using cellular automata like in *The Game of Life*.
It is a work in progress, but already shows off a few different particle types that have some
basic rules they follow. Not meant to be a full functioning simulator, but rather a way for me
to learn more C++ and SFML.

### Prerequisites

- C++, C/C++ compiler, cmake, SFML

### How to build/run

Here are the steps I go through to build/run this easily

1. Clone the repo locally
2. cd into the ParticleGame directory
3. run `mkdir build` and cd into the build directory
4. run `cmake ..` which will create and put all build files into the build directory based on the CMakeLists.txt in the root directory
5. run `make` inside the build directory to create the executable
6. run `./ParticleGame` in the build directory to start up the game!

### Current Particles:

* Sand: Falls down and spreads out
* Water: Flows down and to the sides
* Wood: Stationary and flammable
* Fire: Burns up any flammable particles nearby

### Upcoming Additions (maybe):

* Buttons to change particle type being drawn
* Ability to erase particles
* Hopefully slightly better visuals for fire
* Smoke particle
* Acid particle
