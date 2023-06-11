cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCES main.cpp include/Particle.cpp include/Grid.cpp include/Button.cpp)

project(ParticleGame)
include(CTest)
add_executable(ParticleGame ${SOURCES})
add_test(test ParticleGame)
target_include_directories(ParticleGame PUBLIC /usr/include/SFML)
target_include_directories(ParticleGame PRIVATE include)
target_link_libraries(ParticleGame sfml-system sfml-window sfml-graphics)
