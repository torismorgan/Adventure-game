#include "Game.hpp"
#include "ConcreteItems.hpp" // Includes Flashlight, Key, Amulet
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

    // Create doors with locks
    foyer->setExit("north", library, std::make_shared<Key>("Key to Library"));
    library->setExit("down", basement, std::make_shared<Key>("Key to Basement"));

    // Add items to rooms
    foyer->addItem(std::make_shared<Flashlight>());
    library->addItem(std::make_shared<Key>("Key to Basement"));
    basement->addItem(std::make_shared<Amulet>());

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
    std::cout << "Your goal is to explore the rooms, solve puzzles, and find the Amulet of Dali the Great.\n";
    std::cout << "Available commands:\n";
    std::cout << "- look: Look around the current room.\n";
    std::cout << "- take <item>: Take an item from the room.\n";
    std::cout << "- drop <item>: Drop an item from your inventory.\n";
    std::cout << "- use <item>: Use an item from your inventory.\n";
    std::cout << "- move <direction>: Move to another room (if possible).\n";
    std::cout << "- help: Display these instructions again.\n";
    std::cout << "- quit: Exit the game.\n";
}

// Process the player's input
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
        auto item = currentRoom->findItem(itemName);

        if (item) {
            player->pickUp(item);
            currentRoom->removeItem(item);
            std::cout << "You picked up the " << itemName << ".\n";
        } else {
            std::cout << "There is no " << itemName << " here.\n";
        }
    } 
    else if (command.rfind("drop", 0) == 0) {
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
            std::cout << "You don't have " << itemName << " in your inventory.\n";
        }
    } 
    else if (command.rfind("use", 0) == 0) {
        if (command.size() <= 4) {
            std::cout << "What do you want to use?\n";
            return;
        }

        std::string itemName = command.substr(4);
        auto item = player->findItemInInventory(itemName);

        if (item) {
            item->use();
        } else {
            std::cout << "You don't have " << itemName << " in your inventory.\n";
        }
    } 
    else if (command.rfind("move", 0) == 0) {
        if (command.size() <= 5) {
            std::cout << "Move where? Please specify a direction.\n";
            return;
        }

        std::string direction = command.substr(5);
        auto currentRoom = player->getCurrentRoom();
        auto door = currentRoom->getExit(direction);

        if (door) {
            if (door->isLocked()) {
                auto requiredKey = door->getRequiredKey();
                if (player->hasItem(requiredKey)) {
                    std::cout << "You unlocked the door with " << requiredKey->getName() << ".\n";
                    door->unlock();
                    player->move(direction);
                } else {
                    std::cout << "The door is locked. You need " << requiredKey->getName() << " to open it.\n";
                }
            } else {
                player->move(direction);
            }
        } else {
            std::cout << "There is no exit in that direction.\n";
        }
    } 
    else if (command == "help") {
        displayInstructions();
    } 
    else if (command == "quit") {
        std::cout << "Thanks for playing! Goodbye.\n";
        isGameOver = true;
    } 
    else {
        std::cout << "Unknown command. Type 'help' for a list of commands.\n";
    }
}

// Check if the win condition is met
bool Game::checkWinCondition() {
    auto currentRoom = player->getCurrentRoom();
    for (const auto& item : currentRoom->getItems()) {
        if (item->getName() == "Amulet") {
            std::cout << "Congratulations! You have found the Amulet of Dali the Great and won the game!\n";
            return true;
        }
    }
    return false;
}

// Start the game loop
void Game::start() {
    displayInstructions();

    while (!isGameOver) {
        std::cout << "> ";
        std::string command;
        std::getline(std::cin, command);

        processCommand(command);

        if (checkWinCondition()) {
            isGameOver = true;
        }
    }
}

