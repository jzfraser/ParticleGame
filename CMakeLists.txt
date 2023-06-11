cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCES main.cpp src/Particle.cpp src/ParticleGrid.cpp src/Button.cpp)

project(ParticleGame)
include(CTest)
add_executable(ParticleGame ${SOURCES})
add_test(test ParticleGame)
target_include_directories(ParticleGame PUBLIC /opt/homebrew/Cellar/sfml/2.5.1_2/include/)
target_include_directories(ParticleGame PRIVATE src)
target_include_directories(ParticleGame PRIVATE include)
target_link_libraries(ParticleGame
  /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-system.dylib
  /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-window.dylib
  /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-graphics.dylib)
