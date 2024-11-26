#include "Game.hpp"
#include "ConcreteItems.hpp"
#include <iostream>
#include <algorithm>

Game::Game() : isGameOver(false) {
    setupGame();
}

void Game::setupGame() {
    auto foyer = std::make_shared<Room>("You are in a dimly lit foyer.");
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
    }
    else if (command.rfind("take", 0) == 0) {
        if (command.size() <= 5) {
            std::cout << "What do you want to take?\n";
            return;
        }

        std::string itemName = command.substr(5);
        auto currentRoom = player->getCurrentRoom();
        auto& items = currentRoom->getItems();

        auto it = std::find_if(items.begin(), items.end(),
            [&itemName](const std::shared_ptr<Item>& item) {
                return item->getName() == itemName;
            });

        if (it != items.end()) {
            player->pickUp(*it);
            currentRoom->removeItem(*it);
            std::cout << "You picked up the " << itemName << ".\n";
        } else {
            std::cout << "There is no " << itemName << " here.\n";
        }
    }
    else if (command.rfind("move", 0) == 0) {
        if (command.size() <= 5) {
            std::cout << "Move where? Please specify a direction.\n";
            return;
        }

        std::string direction = command.substr(5);
        if (!player->move(direction)) {
            std::cout << "You can't move that way!\n";
        }
    }
    else if (command == "quit") {
        std::cout << "Exiting game...\n";
        isGameOver = true; // Set isGameOver to true to exit the loop
    }
    else {
        std::cout << "Unknown command.\n";
    }
}


void Game::start() {
    std::cout << "Welcome to the adventure game!\n";

    std::string command;
    while (!isGameOver) {
        std::cout << "> ";
        std::getline(std::cin, command);
        processCommand(command);

        //if (command == "quit") break;
    }
    std::cout << "Thanks fo playing\n";
}


