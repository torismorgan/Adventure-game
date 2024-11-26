#include "Game.hpp"
#include "ConcreteItems.hpp"
#include <iostream>

Game::Game() {
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
    } else if (command.rfind("take", 0) == 0) { // Check if the command starts with "take"
        std::string itemName = command.substr(5); // Extract item name after "take "
        auto currentRoom = player->getCurrentRoom();
        auto& items = currentRoom->getItems();

        // Find the item in the room
        auto it = std::find_if(items.begin(), items.end(),
            [&itemName](const std::shared_ptr<Item>& item) {
                return item->getName() == itemName;
            });

        if (it != items.end()) {
            player->pickUp(*it); // Pick up the item
            currentRoom->removeItem(*it); // Remove from room
            std::cout << "You picked up the " << itemName << ".\n";
        } else {
            std::cout << "There is no " << itemName << " here.\n";
        }
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


