#include "Game.hpp"
#include "ConcreteItems.hpp"
#include <iostream>

Game::Game() {
    setupGame();
}

void Game::setupGame() {
    auto foyer = std::make_shared<Room>("A dimly lit foyer.");
    auto library = std::make_shared<Room>("A grand library filled with books.");
    auto basement = std::make_shared<Room>("A dark, damp basement.");

    foyer->setExit("north", library);
    library->setExit("south", foyer);
    library->setExit("down", basement);

    foyer->addItem(std::make_shared<Flashlight>());
    library->addItem(std::make_shared<Key>());

    rooms["foyer"] = foyer;
    rooms["library"] = library;
    rooms["basement"] = basement;

    player = std::make_shared<Player>(foyer);
}

void Game::processCommand(const std::string& command) {
    if (command == "look") {
        player->getCurrentRoom()->describe();
    } else if (command.rfind("move", 0) == 0) {
        std::string direction = command.substr(5);
        if (!player->move(direction)) {
            std::cout << "You can't move that way!\n";
        }
    } else if (command == "quit") {
        std::cout << "Exiting game...\n";
        return;
    } else {
        std::cout << "Unknown command.\n";
    }
}

void Game::start() {
    std::cout << "Welcome to the adventure game!\n";

    std::string command;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);
        processCommand(command);

        if (command == "quit") break;
    }
}



