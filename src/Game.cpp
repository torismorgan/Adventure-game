#include "ConcreteItems.hpp"
#include "GameDisplay.hpp"
#include <iostream>
#include <algorithm>
#include "Game.hpp"
#include "Room.hpp"
#include "Player.hpp"
#include "ConcreteItems.hpp"
#include "GameDisplay.hpp"
#include <iostream>
#include <algorithm>

// Constructor
Game::Game() : isGameOver(false) {
    setupGame();
}

// Destructor
Game::~Game() = default;

// Setup game environment
void Game::setupGame() {
    // Create rooms
    auto foyer = std::make_shared<Room>("A dimly lit foyer.");
    auto library = std::make_shared<Room>("A grand library filled with dusty books.");
    auto basement = std::make_shared<Room>("A dark, damp basement with a chest in the corner.");

    // Set room exits
    foyer->setExit("north", library);
    library->setExit("south", foyer);
    library->setExit("down", basement);

    // Lock the basement door with a key
    library->lockExit("down", std::make_shared<Flashlight>());

    // Add items to rooms
    foyer->addItem(std::make_shared<Flashlight>());
    library->addItem(std::make_shared<Amulet>());

    // Set the player's starting room
    player = std::make_shared<Player>(foyer);
}

// Display game instructions
void Game::displayInstructions() const {
    std::cout << "Welcome to the adventure game!\n"
              << "Your goal is to find the Amulet of Dali the Great hidden in the basement.\n"
              << "Commands:\n"
              << "  look          - Look around the room.\n"
              << "  move <dir>    - Move in the specified direction (e.g., 'move north').\n"
              << "  take <item>   - Pick up an item in the room.\n"
              << "  drop <item>   - Drop an item from your inventory into the room.\n"
              << "  use <item>    - Use an item in your inventory.\n"
              << "  inventory     - View the items in your inventory.\n"
              << "  help          - Display these instructions again.\n"
              << "  quit          - Exit the game.\n";
}

// Start the game
void Game::start() {
    GameDisplay display;

    display.displayWelcomeMessage();
    displayInstructions();
    std::string command;

    while (!isGameOver) {
        std::cout << "> ";
        std::getline(std::cin, command);
        processCommand(command);

        if (checkWinCondition()) {
            display.displayWinMessage();
            isGameOver = true;
        }
    }

    display.displayGoodbyeMessage();
}

// Process player commands
void Game::processCommand(const std::string& command) {
    auto currentRoom = player->getCurrentRoom();
    GameDisplay display;

    if (command == "look") {
        currentRoom->describe();
    } else if (command.find("move") == 0) {
        std::string direction = command.substr(5);
        auto exitDoor = currentRoom->getExit(direction);
        if (exitDoor) {
            if (exitDoor->isLocked()) {
                std::cout << "The door is locked. You need a key to open it.\n";
            } else {
                player->move(direction);
            }
        } else {
            std::cout << "There is no exit in that direction.\n";
        }
    } else if (command.find("take") == 0) {
        std::string itemName = command.substr(5);
        const auto& items = currentRoom->getItems();
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
    } else if (command.find("drop") == 0) {
        std::string itemName = command.substr(5);
        auto item = player->findItemInInventory(itemName);
        if (item) {
            player->dropItem(item);
            currentRoom->addItem(item);
            std::cout << "You dropped the " << itemName << ".\n";
        } else {
            std::cout << "You don't have " << itemName << " in your inventory.\n";
        }
    } else if (command.find("use") == 0) {
        std::string itemName = command.substr(4);
        auto item = player->findItemInInventory(itemName);
        if (item) {
            item->use();
        } else {
            std::cout << "You don't have " << itemName << " in your inventory.\n";
        }
    } else if (command == "inventory") {
        const auto& inventory = player->getInventory();
        if (inventory.empty()) {
            std::cout << "Your inventory is empty.\n";
        } else {
            std::cout << "Your inventory contains:\n";
            for (const auto& item : inventory) {
                std::cout << "- " << item->getName() << "\n";
            }
        }
    } else if (command == "help") {
        displayInstructions();
    } else if (command == "quit") {
        isGameOver = true;
    } else {
        std::cout << "Unknown command. Type 'help' for a list of commands.\n";
    }
}

// Check if the player has won the game
bool Game::checkWinCondition() const {
    auto currentRoom = player->getCurrentRoom();
    if (currentRoom->getDescription() == "A dark, damp basement with a chest in the corner.") {
        std::cout << "You found the chest containing the Amulet of Dali the Great!\n";
        return true;
    }
    return false;
}

