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
  auto foyer = std::make_shared<Room>("You are in a dimly lit foyer.");
  auto library = std::make_shared<Room>("A grand library filled with books.");
  auto basement = std::make_shared<Room>("A dark, damp basement.");

  foyer->setExit("north", library);
  library->setExit("south", foyer);
  library->setExit("down", basement);
  basement->setExit("up", library);

  foyer->addItem(std::make_shared<Flashlight>());
  library->addItem(std::make_shared<Key>());

  rooms["foyer"] = foyer;
  rooms["library"] = library;
  rooms["basement"] = basement;

  player = std::make_shared<Player>(foyer);
}

// Process the player's input
void Game::processCommand(const std::string& command) {
  GameDisplay display;

  if (command == "look") {
    display.displayRoomDescription(player->getCurrentRoom().get());
  } else if (command.rfind("take", 0) == 0) {
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

  } else if (command.rfind("move", 0) == 0) {
    if (command.size() <= 5) {
      display.displayError("Move where? Please specify a direction.");
      return;
    }

    std::string direction = command.substr(5);
    if (!player->move(direction)) {
      display.displayError("You can't move that way!");
    }
  } else if (command == "help") {
    display.displayHelp();
  } else if (command == "quit") {
    std::cout << "Exiting game...\n";
    isGameOver = true;
  } else {
    display.displayError(
        "Unknown command. Type 'help' for a list of commands.");
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
