#include "Game.hpp"
#include "ConcreteItems.hpp"
#include <iostream>
#include <algorithm>

// Constructor: Initialize game state
Game::Game() : isGameOver(false) {
    setupGame();
}

// Destructor: Clean up resources
Game::~Game() {
    rooms.clear();
}

// Set up the game environment
void Game::setupGame() {
    // Create rooms
    auto foyer = std::make_shared<Room>("A dimly lit foyer.");
    auto library = std::make_shared<Room>("A grand library filled with dusty books.");
    auto basement = std::make_shared<Room>("A dark, damp basement.");

    // Create items
    auto flashlight = std::make_shared<Flashlight>();
    auto keyToLibrary = std::make_shared<Key>("Key to Library");
    auto keyToBasement = std::make_shared<Key>("Key to Basement");
    auto amulet = std::make_shared<Amulet>();

    // Add items to rooms
    foyer->addItem(flashlight);
    foyer->addItem(keyToLibrary);
    library->addItem(keyToBasement);
    basement->addItem(amulet);

    // Set room exits
    foyer->setExit("north", library);
    library->setExit("south", foyer);
    library->setExit("down", basement);
    basement->setExit("up", library);

    // Lock the basement door
    library->lockExit("down", keyToBasement);

    // Add rooms to the map
    rooms["foyer"] = foyer;
    rooms["library"] = library;
    rooms["basement"] = basement;

    // Set player's starting room
    player = std::make_shared<Player>(foyer);
}

// Display game instructions
void Game::displayInstructions() const {
    std::cout << "Welcome to the Adventure Game!\n";
    std::cout << "Instructions:\n";
    std::cout << "- Use 'look' to see the room's description and items.\n";
    std::cout << "- Use 'take <item>' to pick up an item.\n";
    std::cout << "- Use 'drop <item>' to drop an item from your inventory.\n";
    std::cout << "- Use 'inventory' to see your inventory.\n";
    std::cout << "- Use 'move <direction>' to move between rooms.\n";
    std::cout << "- Use 'use <item>' to use an item.\n";
    std::cout << "- Type 'help' to see these instructions again.\n";
    std::cout << "- Type 'quit' to exit the game.\n\n";
}

// Process player commands
void Game::processCommand(const std::string& command) {
    if (command == "look") {
        auto currentRoom = player->getCurrentRoom();
        currentRoom->describe();
    } else if (command.rfind("take", 0) == 0) {
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
    } else if (command.rfind("drop", 0) == 0) {
        if (command.size() <= 5) {
            std::cout << "What do you want to drop?\n";
            return;
        }

        std::string itemName = command.substr(5);
        auto item = player->findItemInInventory(itemName);
        if (item) {
            player->dropItem(item);
            player->getCurrentRoom()->addItem(item);
            std::cout << "You dropped the " << itemName << ".\n";
        } else {
            std::cout << "You don't have a " << itemName << " in your inventory.\n";
        }
    } else if (command == "inventory") {
        auto inventory = player->getInventory();
        std::cout << "Your inventory contains:\n";
        for (const auto& item : inventory) {
            std::cout << "- " << item->getName() << "\n";
        }
    } else if (command.rfind("move", 0) == 0) {
        if (command.size() <= 5) {
            std::cout << "Move where? Please specify a direction.\n";
            return;
        }

        std::string direction = command.substr(5);
        if (!player->move(direction)) {
            std::cout << "The door is locked. You need a key to open it.\n";
        }
    } else if (command.rfind("use", 0) == 0) {
        if (command.size() <= 4) {
            std::cout << "What do you want to use?\n";
            return;
        }

        std::string itemName = command.substr(4);
        auto item = player->findItemInInventory(itemName);
        if (item) {
            item->use();
        } else {
            std::cout << "You don't have a " << itemName << " in your inventory.\n";
        }
    } else if (command == "help") {
        displayInstructions();
    } else if (command == "quit") {
        std::cout << "Thanks for playing! Goodbye.\n";
        isGameOver = true;
    } else {
        std::cout << "Unknown command. Type 'help' for a list of commands.\n";
    }
}

// Check if the win condition is met
bool Game::checkWinCondition() {
    auto currentRoom = player->getCurrentRoom();
    auto inventory = player->getInventory();

    for (const auto& item : inventory) {
        if (item->getName() == "Amulet" &&
            currentRoom->getDescription() == "A dark, damp basement.") {
            return true;
        }
    }
    return false;
}

// Start the game loop
void Game::start() {
    displayInstructions();

    std::string command;
    while (!isGameOver) {
        std::cout << "> ";
        std::getline(std::cin, command);

        processCommand(command);

        if (checkWinCondition()) {
            std::cout << "Congratulations! You found the Amulet of Dali the Great!\n";
            std::cout << "You have won the game!\n";
            isGameOver = true;
        }
    }
}


