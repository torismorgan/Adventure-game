#include "Game.hpp"

#include <algorithm>
#include <iostream>
#include "ConcreteItems.hpp"
#include "Game.hpp"
#include <iostream>
#include <algorithm>

Game::Game() {
    setupGame();
}

void Game::setupGame() {
    auto foyer = std::make_shared<Room>("A dimly lit foyer.");
    auto library = std::make_shared<Room>("A grand library filled with dusty books.");
    auto basement = std::make_shared<Room>("A dark, damp basement.");

    auto foyerKey = std::make_shared<Key>();
    foyerKey->setName("Key to Library");
    foyer->addItem(foyerKey);

    auto basementKey = std::make_shared<Key>();
    basementKey->setName("Key to Chest");
    library->addItem(basementKey);

    auto amulet = std::make_shared<Amulet>();
    amulet->setName("Amulet of Dali the Great");

    auto chest = std::make_shared<Flashlight>();
    chest->setName("Chest");
    basement->addItem(chest);

    foyer->setExitWithDoor("north", library, std::make_shared<Door>(true, foyerKey));
    library->setExitWithDoor("down", basement, std::make_shared<Door>(true, basementKey));

    rooms["foyer"] = foyer;
    rooms["library"] = library;
    rooms["basement"] = basement;

    player = std::make_shared<Player>(foyer);
}

void Game::processCommand(const std::string& command) {
    if (command == "look") {
        player->getCurrentRoom()->describe();
    } else if (command.rfind("take", 0) == 0) {
        std::string itemName = command.substr(5);
        auto room = player->getCurrentRoom();
        auto& items = room->getItems();
        auto it = std::find_if(items.begin(), items.end(),
            [&itemName](const std::shared_ptr<Item>& item) {
                return item->getName() == itemName;
            });

        if (it != items.end()) {
            player->pickUp(*it);
            room->removeItem(*it);
            std::cout << "You picked up " << itemName << ".\n";
        } else {
            std::cout << "There is no " << itemName << " here.\n";
        }
    }
}

void Game::start() {
    std::cout << "Welcome to the adventure game!\n";
    std::string command;
    while (!isGameOver) {
        std::cout << "> ";
        std::getline(std::cin, command);
        processCommand(command);
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
