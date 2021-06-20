#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "include/Constants.hpp"
#include "include/Grid.hpp"
#include "include/Button.hpp"

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

void createButtons(Button* btns, sf::Font &font) {
    btns[0] = Button("Sand", {50, 25}, 15, sf::Color::White, sf::Color::Black, SAND);
    btns[0].setFont(font);
    btns[0].setPosition({740, 10});
    btns[1] = Button("Water", {50, 25}, 15, sf::Color::White, sf::Color::Black, WATER);
    btns[1].setFont(font);
    btns[1].setPosition({740, 40});
    btns[2] = Button("Wood", {50, 25}, 15, sf::Color::White, sf::Color::Black, WOOD);
    btns[2].setFont(font);
    btns[2].setPosition({740, 70});
    btns[3] = Button("Fire", {50, 25}, 15, sf::Color::White, sf::Color::Black, FIRE);
    btns[3].setFont(font);
    btns[3].setPosition({740, 100});
}

void drawButtons(Button* btns, sf::RenderWindow &window) {
    for (int i = 0; i < 4; i++) {
        btns[i].drawTo(window);
    }
}

int mouseOverButton(Button* btns, sf::RenderWindow &window) {
    for (int i = 0; i < 4; i++) {
        if (btns[i].isMouseOver(window))
            return i;
    }
    return -1;
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
    Button btns[4];
    createButtons(btns, droidSansMono);

    while (window.isOpen()) {
        float dt = deltaClock.restart().asSeconds();
        int fps = 1 / dt;
        // std::cout << fps << "\n";
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                int btnNum = mouseOverButton(btns, window);
                if (btnNum >= 0) {
                    spawnType = btns[btnNum].getType();
                } else {
                    spawning = true;
                }
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
        drawButtons(btns, window);
        window.display();
    }

    return 0;
}
