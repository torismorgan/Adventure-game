#include "Game.hpp"

#include <algorithm>
#include <iostream>
#include "ConcreteItems.hpp"
#include "GameDisplay.hpp"

// Constructor: Initialize game state
Game::Game() : isGameOver(false) { setupGame(); }

// Destructor: Clean up resources
Game::~Game() { rooms.clear(); }

void Game::setupGame() {
    auto foyer = std::make_shared<Room>("A dimly lit foyer.");
    auto library = std::make_shared<Room>("A grand library filled with dusty books.");
    auto basement = std::make_shared<Room>("A dark, damp basement.");

    // Create keys
    auto foyerKey = std::make_shared<Key>();
    foyerKey->setName("Key to Library");
    foyer->addItem(foyerKey);

    auto basementKey = std::make_shared<Key>();
    basementKey->setName("Key to Chest");
    library->addItem(basementKey);

    // Add exits with doors
    foyer->setExitWithDoor("north", library, std::make_shared<Door>(true, foyerKey));
    library->setExitWithDoor("down", basement, std::make_shared<Door>(true, basementKey));

    // Add chest to the basement
    auto chest = std::make_shared<Item>();
    chest->setName("Chest");
    basement->addItem(chest);

    // Add rooms to map
    rooms["foyer"] = foyer;
    rooms["library"] = library;
    rooms["basement"] = basement;

    // Set player's starting room
    player = std::make_shared<Player>(foyer);
}



// Process the player's input
void Game::processCommand(const std::string& command) {
    GameDisplay display;

    if (command == "look") {
        display.displayRoomDescription(player->getCurrentRoom().get());
    }
    else if (command.rfind("take", 0) == 0) {
        if (command.size() <= 5) {
            display.displayError("What do you want to take?");
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
            display.displayError("There is no " + itemName + " here.");
        }
    }
    else if (command.rfind("use key", 0) == 0) { // Unlock door
        std::string direction = command.substr(8); // Extract direction
        auto currentRoom = player->getCurrentRoom();
        auto door = currentRoom->getDoor(direction);

        if (door && door->getIsLocked()) {
            auto inventory = player->getInventory();
            auto it = std::find_if(inventory.begin(), inventory.end(),
                [](const std::shared_ptr<Item>& item) { return item->getName().find("Key") != std::string::npos; });

            if (it != inventory.end() && door->unlock(*it)) {
                std::cout << "You unlocked the door to the " << direction << ".\n";
            } else {
                std::cout << "You don't have the correct key to unlock this door.\n";
            }
        } else {
            std::cout << "There is no locked door in that direction.\n";
        }
    }
    else if (command.rfind("move", 0) == 0) {
        if (command.size() <= 5) {
            display.displayError("Move where? Please specify a direction.");
            return;
        }

        std::string direction = command.substr(5);
        auto currentRoom = player->getCurrentRoom();

        if (currentRoom->isDoorLocked(direction)) {
            std::cout << "The door to the " << direction << " is locked. Use a key to unlock it.\n";
        } else if (!player->move(direction)) {
            display.displayError("You can't move that way!");
        }
    }
    else if (command == "open chest") { // Open chest in the basement
        auto currentRoom = player->getCurrentRoom();
        if (currentRoom->getDescription() == "A dark, damp basement.") {
            auto inventory = player->getInventory();
            auto it = std::find_if(inventory.begin(), inventory.end(),
                [](const std::shared_ptr<Item>& item) { return item->getName() == "Key to Chest"; });

            if (it != inventory.end()) {
                std::cout << "You used the key to open the chest and found the Amulet of Dali the Great!\n";
                isGameOver = true; // End the game
            } else {
                std::cout << "You need a key to open the chest.\n";
            }
        } else {
            std::cout << "There is no chest here to open.\n";
        }
    }
    else if (command == "inventory") {
        const auto& inventory = player->getInventory();
        if (inventory.empty()) {
            std::cout << "Your inventory is empty.\n";
        } else {
            std::cout << "You are carrying:\n";
            for (const auto& item : inventory) {
                std::cout << "- " << item->getName() << "\n";
            }
        }
    }
    else if (command == "quit") {
        std::cout << "Exiting game...\n";
        isGameOver = true;
    }
    else {
        display.displayError("Unknown command. Type 'help' for a list of commands.");
    }
}



// Check if the win condition is met
bool Game::checkWinCondition() {
  auto currentRoom = player->getCurrentRoom();
  if (currentRoom->getDescription() == "A dark, damp basement.") {
    return true;
  }
  return false;
}

// Start the game loop
void Game::start() {
  GameDisplay display;
  display.displayWelcomeMessage();
  display.displayHelp();

  std::cout << "You can type 'help' anytime to see the instructions again.\n";

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
