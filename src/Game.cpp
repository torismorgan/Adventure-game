#include "Game.hpp"

#include <algorithm>
#include <iostream>
#include "ConcreteItems.hpp"
#include "Game.hpp"
#include <iostream>
#include <algorithm>


// Constructor
Game::Game() : isGameOver(false) {
    setupGame();
}

// Destructor
Game::~Game() {
    rooms.clear();
}

// Display Instructions
void Game::displayInstructions() const {
    std::cout << "Welcome to the Adventure Game!\n";
    std::cout << "Instructions:\n";
    std::cout << "- Use 'look' to view the room and items in it.\n";
    std::cout << "- Use 'take [item]' to pick up an item.\n";
    std::cout << "- Use 'drop [item]' to drop an item in the room.\n";
    std::cout << "- Use 'use [item]' to use an item from your inventory.\n";
    std::cout << "- Use 'move [direction]' to move to another room.\n";
    std::cout << "- Use 'quit' to end the game.\n";
    std::cout << "\nYour goal is to find the long-lost Amulet of Dali the Great hidden in the basement.\n";
}

// Setup Game Environment
void Game::setupGame() {
    auto foyer = std::make_shared<Room>("A dimly lit foyer.");
    auto library = std::make_shared<Room>("A grand library filled with dusty books.");
    auto basement = std::make_shared<Room>("A dark, damp basement.");

    // Set room exits
    foyer->setExit("north", library);
    library->setExit("south", foyer);
    library->setExit("down", basement);
    basement->setExit("up", library);

    // Add items to rooms
    foyer->addItem(std::make_shared<Flashlight>());
    library->addItem(std::make_shared<Key>("Key to Basement"));
    basement->addItem(std::make_shared<Amulet>());

    // Set locked doors
    library->getExit("down")->lock(std::make_shared<Key>("Key to Basement"));

    // Add rooms to map
    rooms["foyer"] = foyer;
    rooms["library"] = library;
    rooms["basement"] = basement;

    // Set player's starting room
    player = std::make_shared<Player>(foyer);
}

// Process Commands
void Game::processCommand(const std::string& command) {
    if (command == "look") {
        auto currentRoom = player->getCurrentRoom();
        currentRoom->enter();
    } else if (command.rfind("take", 0) == 0) {
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
        std::string itemName = command.substr(5);
        auto inventory = player->getInventory();

        auto it = std::find_if(inventory.begin(), inventory.end(),
            [&itemName](const std::shared_ptr<Item>& item) {
                return item->getName() == itemName;
            });

        if (it != inventory.end()) {
            player->dropItem(*it);
            player->getCurrentRoom()->addItem(*it);
            std::cout << "You dropped the " << itemName << ".\n";
        } else {
            std::cout << "You don't have " << itemName << " in your inventory.\n";
        }
    } else if (command.rfind("use", 0) == 0) {
        std::string itemName = command.substr(4);
        auto inventory = player->getInventory();

        auto it = std::find_if(inventory.begin(), inventory.end(),
            [&itemName](const std::shared_ptr<Item>& item) {
                return item->getName() == itemName;
            });

        if (it != inventory.end()) {
            (*it)->use();
        } else {
            std::cout << "You don't have " << itemName << " in your inventory.\n";
        }
    } else if (command.rfind("move", 0) == 0) {
        std::string direction = command.substr(5);
        if (!player->move(direction)) {
            std::cout << "You can't move that way!\n";
        }
    } else if (command == "help") {
        displayInstructions();
    } else if (command == "quit") {
        std::cout << "Thanks for playing! Goodbye!\n";
        isGameOver = true;
    } else {
        std::cout << "Unknown command. Type 'help' for a list of commands.\n";
    }
}

// Check Win Condition
bool Game::checkWinCondition() {
    auto currentRoom = player->getCurrentRoom();
    return currentRoom->getDescription() == "A dark, damp basement." &&
           player->hasItem(std::make_shared<Amulet>());
}

// Start Game Loop
void Game::start() {
    displayInstructions();
    std::string command;
    while (!isGameOver) {
        std::cout << "> ";
        std::getline(std::cin, command);
        processCommand(command);

        if (checkWinCondition()) {
            std::cout << "Congratulations! You found the Amulet of Dali the Great and won the game!\n";
            isGameOver = true;
        }
    }
}
