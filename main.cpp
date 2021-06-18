#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "include/Grid.hpp"
#include "include/Button.hpp"

const uint32_t WIN_WIDTH = 800;
const uint32_t WIN_HEIGHT = 600;
const uint32_t WORLD_SIZE = 100;
const uint32_t PARTICLE_WIDTH = WIN_WIDTH / WORLD_SIZE;
const uint32_t PARTICLE_HEIGHT = WIN_HEIGHT / WORLD_SIZE;

void spawnParticles(Grid* world, ParticleType t, int x, int y) {
    int col = x / PARTICLE_WIDTH;
    int row = y / PARTICLE_HEIGHT;
    // std::cout << row << " " << col << "\n";
    if (row < world->size && col < world->size) {
        if (world->slotIsEmpty(row, col)) {
            world->grid[row][col].setType(t);
        } if (row < world->size - 1 && world->slotIsEmpty(row + 1, col)) {
            world->grid[row + 1][col].setType(t);
        } if (col > 0 && world->slotIsEmpty(row, col - 1)) {
            world->grid[row][col - 1].setType(t);
        } if (col < world->size - 1 && world->slotIsEmpty(row, col + 1)) {
            world->grid[row][col + 1].setType(t);
        } if (row > 0 && world->slotIsEmpty(row - 1, col)) {
            world->grid[row - 1][col].setType(t);
        }
    }
}

void drawGrid(Grid* world, int size, sf::RenderWindow* window) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            sf::RectangleShape particle(sf::Vector2f(PARTICLE_WIDTH, PARTICLE_HEIGHT));
            particle.setPosition(col * PARTICLE_WIDTH, row * PARTICLE_HEIGHT);
            switch (world->grid[row][col].color) {
                case YELLOW:
                    particle.setFillColor(sf::Color::Yellow);
                    break;
                case BLUE:
                    particle.setFillColor(sf::Color::Blue);
                    break;
                case BROWN:
                    particle.setFillColor(sf::Color(102, 51, 0));
                    break;
                case RED:
                    particle.setFillColor(sf::Color::Red);
                    break;
                case BLACK:
                default:
                    particle.setFillColor(sf::Color::Black);
            }
            window->draw(particle);
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Sand Game");
    window.setFramerateLimit(60);
    sf::Clock deltaClock;
    sf::Font droidSansMono;
    droidSansMono.loadFromFile("../include/DroidSansMono.ttf");

    Grid world = Grid(WORLD_SIZE);

    bool spawning = false;
    ParticleType spawnType = EMPTY;
    Button btnSand("Sand", {50, 25}, 15, sf::Color::White, sf::Color::Black);
    btnSand.setFont(droidSansMono);
    btnSand.setPosition({740, 10});

    while (window.isOpen()) {
        float dt = deltaClock.restart().asSeconds();
        int fps = 1 / dt;
        // std::cout << fps << "\n";
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (btnSand.isMouseOver(window)) {
                    spawnType = SAND;
                } else {
                    spawning = true;
                }
                // switch (event.mouseButton.button) {
                //     case sf::Mouse::Button::Left:
                //         spawnType = FIRE;
                //         break;
                //     case sf::Mouse::Button::Right:
                //         spawnType = SAND;
                //         break;
                //     case sf::Mouse::Button::Middle:
                //         spawnType = WOOD;
                //         break;
                //     default:
                //         spawnType = SAND;
                // }
            }
            if (event.type == sf::Event::MouseButtonReleased)
                spawning = false;
        }
        if (spawning) {
            int x = sf::Mouse::getPosition(window).x;
            int y = sf::Mouse::getPosition(window).y;
            spawnParticles(&world, spawnType, x, y);
        }

        world.check();
        window.clear();
        drawGrid(&world, WORLD_SIZE, &window);
        btnSand.drawTo(window);
        window.display();
    }

    return 0;
}
