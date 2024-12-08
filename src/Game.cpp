#include "Game.hpp"

#include <algorithm>
#include <iostream>
#include "ConcreteItems.hpp"
#include "Game.hpp"
#include <iostream>
#include <algorithm>

#include "Game.hpp"
#include <iostream>
#include <algorithm>

// Constructor
Game::Game() : isGameOver(false) {
    setupGame();
}

// Setup the game
void Game::setupGame() {
    auto foyer = std::make_shared<Room>("A dimly lit foyer.");
    auto library = std::make_shared<Room>("A grand library filled with dusty books.");
    auto basement = std::make_shared<Room>("A dark, damp basement.");

    // Items
    auto flashlight = std::make_shared<Flashlight>();
    auto libraryKey = std::make_shared<Key>();
    libraryKey->setName("Key to Library");
    auto chestKey = std::make_shared<Key>();
    chestKey->setName("Key to Chest");
    auto amulet = std::make_shared<Amulet>();

    // Add items to rooms
    foyer->addItem(flashlight);
    foyer->addItem(libraryKey);
    library->addItem(chestKey);
    basement->addItem(amulet);

    // Doors
    foyer->setExitWithDoor("north", library, std::make_shared<Door>(true, libraryKey));
    library->setExitWithDoor("down", basement, std::make_shared<Door>(true, chestKey));

    // Set up rooms in the game
    rooms["foyer"] = foyer;
    rooms["library"] = library;
    rooms["basement"] = basement;

    // Player starts in the foyer
    player = std::make_shared<Player>(foyer);
}

// Process player commands
void Game::processCommand(const std::string& command) {
    if (command == "look") {
        player->getCurrentRoom()->describe();
    } else if (command.rfind("take", 0) == 0) {
        std::string itemName = command.substr(5);
        auto currentRoom = player->getCurrentRoom();
        auto& items = currentRoom->getItems();

        auto it = std::find_if(items.begin(), items.end(), [&itemName](const std::shared_ptr<Item>& item) {
            return item->getName() == itemName;
        });

        if (it != items.end()) {
            player->pickUp(*it);
            currentRoom->removeItem(*it);
            std::cout << "You picked up the " << itemName << ".\n";
        } else {
            std::cout << "There is no " << itemName << " here.\n";
        }
    } else if (command.rfind("move", 0) == 0) {
        std::string direction = command.substr(5);
        auto currentRoom = player->getCurrentRoom();
        if (currentRoom->isDoorLocked(direction)) {
            std::cout << "The door is locked. You need a key to open it.\n";
        } else if (!player->move(direction)) {
            std::cout << "You can't move that way.\n";
        }
    } else if (command.rfind("use", 0) == 0) {
        std::string itemName = command.substr(4);
        auto& inventory = player->getInventory();

        auto it = std::find_if(inventory.begin(), inventory.end(), [&itemName](const std::shared_ptr<Item>& item) {
            return item->getName() == itemName;
        });

        if (it != inventory.end()) {
            (*it)->use();
        } else {
            std::cout << "You don't have " << itemName << " in your inventory.\n";
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

// Display game instructions
void Game::displayInstructions() const {
    std::cout << "Welcome to the Adventure Game!\n"
              << "Your objective is to explore rooms, collect items, and find the Amulet of Dali the Great.\n"
              << "Commands:\n"
              << "- look: Examine your current room.\n"
              << "- take [item]: Pick up an item.\n"
              << "- move [direction]: Move to a different room (north, south, up, down).\n"
              << "- use [item]: Use an item from your inventory.\n"
              << "- help: View the instructions again.\n"
              << "- quit: Exit the game.\n\n";
}

// Start the game
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

// Check if the win condition is met
bool Game::checkWinCondition() {
    auto currentRoom = player->getCurrentRoom();
    return currentRoom->getDescription() == "A dark, damp basement." &&
           std::any_of(player->getInventory().begin(), player->getInventory().end(), [](const std::shared_ptr<Item>& item) {
               return item->getName() == "Amulet of Dali the Great";
           });
}

