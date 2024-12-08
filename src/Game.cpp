#include "Game.hpp"
#include "ConcreteItems.hpp"
#include "GameDisplay.hpp"
#include "Puzzle.hpp"
#include "NPC.hpp"
#include <iostream>
#include <algorithm>

Game::Game() : isGameOver(false) {
    setupGame();
}

Game::~Game() = default;

void Game::setupGame() {
    // Create rooms
    auto foyer = std::make_shared<Room>("You are in a dimly lit foyer. The air is heavy with an eerie silence.");
    auto library = std::make_shared<Room>("A grand library filled with ancient books. Shadows move between the shelves.");
    auto basement = std::make_shared<Room>("A damp, dark basement. The air smells of mildew, and the floor creaks underfoot.");

    // Create puzzles
    auto foyerPuzzle = std::make_shared<Puzzle>("Riddle: 'I'm light as a feather, yet the strongest man can't hold me for more than 5 minutes. What am I?'", "breath");
    auto libraryPuzzle = std::make_shared<Puzzle>("Combination: 'Three explorers set out on an adventure...'", "5 10 15");
    auto basementPuzzle = std::make_shared<Puzzle>("Riddle: 'The more of me you take, the more you leave behind. What am I?'", "footsteps");

    // Create NPCs
    auto whisperingVoice = std::make_shared<NPC>("Whispering Voice", "A faint whisper echoes: 'The library holds the key...'");
    auto ghost = std::make_shared<NPC>("Ghost", "The ghost's chilling presence blocks your way.");

    // Add items
   auto torch = std::make_shared<Torch>();
auto keyitem = std::make_shared<Key>();


    // Room configuration
    foyer->setExit("north", library);
    library->setExit("south", foyer);
    library->setExit("down", basement);

    foyer->addItem(torch);
    library->addItem(keyitem);

    foyer->setPuzzle(foyerPuzzle);
    foyer->setNPC(whisperingVoice);
    library->setPuzzle(libraryPuzzle);
    library->setNPC(ghost);
    basement->setPuzzle(basementPuzzle);

    // Set starting room
    player = std::make_shared<Player>(foyer);
}

void Game::displayInstructions() const {
    std::cout << "Welcome to Haunted Manor Adventure!\n"
              << "Your goal is to find the amulet and restore the manor.\n"
              << "Commands:\n"
              << "  look          - Look around the room.\n"
              << "  move <dir>    - Move in a direction (e.g., 'move north').\n"
              << "  take <item>   - Take an item in the room.\n"
              << "  drop <item>   - Drop an item from your inventory.\n"
              << "  use <item>    - Use an item in your inventory.\n"
              << "  solve         - Solve a puzzle in the room.\n"
              << "  inventory     - View your inventory.\n"
              << "  quit          - Exit the game.\n";
}

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

void Game::processCommand(const std::string& command) {
    auto currentRoom = player->getCurrentRoom();
    GameDisplay display;

    if (command == "look") {
        currentRoom->describe();
    } else if (command.find("move") == 0) {
        std::string direction = command.substr(5);
        player->move(direction);
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
    } else if (command == "solve") {
        auto puzzle = currentRoom->getPuzzle();
        if (puzzle && !puzzle->getIsSolved()) {
            std::cout << puzzle->getDescription() << "\n";
            std::cout << "Answer: ";
            std::string answer;
            std::getline(std::cin, answer);
            if (puzzle->attemptSolution(answer)) {
                std::cout << "You solved the puzzle!\n";
            } else {
                std::cout << "That's not correct.\n";
            }
        } else {
            std::cout << "There is no puzzle to solve here.\n";
        }
    } else if (command.find("use") == 0) {
        std::string itemName = command.substr(4);
        auto item = player->findItemInInventory(itemName);
        if (item) {
            if (item->getName() == "Torch") {
                player->lightTorch();
            } else {
                std::cout << "You can't use that item here.\n";
            }
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
    } else if (command == "quit") {
        isGameOver = true;
    } else {
        std::cout << "Unknown command. Type 'help' for a list of commands.\n";
    }
}

bool Game::checkWinCondition() {
    auto currentRoom = player->getCurrentRoom();
    auto amulet = player->findItemInInventory("Amulet");
    if (currentRoom->getDescription().find("basement") != std::string::npos && amulet) {
        std::cout << "The amulet glows brightly, banishing the darkness. You have restored the manor!\n";
        return true;
    }
    return false;
}

