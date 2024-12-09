#include "Game.hpp"
#include "ConcreteItems.hpp"
#include "ConcreteNPCS.hpp"
#include <iostream>
#include <algorithm>

Game::Game() : isGameOver(false) {
    setupGame();
}

Game::~Game() = default;

void Game::setupGame() {
    auto torch = std::make_shared<Torch>();
    auto keyItem = std::make_shared<Key>();
    auto amulet = std::make_shared<Amulet>();

    auto foyer = std::make_shared<Room>(
        "A dimly lit foyer. You feel a chill in your spine.\n The room is locked; "
        "to leave, you must solve the puzzle.");
    auto library = std::make_shared<Room>(
        "A grand library filled with dusty books and an evil ghost. The ghost blocks your way forward.\n"
        " Use something to scare it away");
    auto basement = std::make_shared<Room>(
        "A damp, dark basement. The air is heavy, and a locked chest is in the corner.");

    foyer->addItem(torch);
    library->addItem(keyItem);

    auto whisperingVoice = std::make_shared<WhisperingVoice>();
    auto ghost = std::make_shared<Ghost>();

    foyer->setNPC(whisperingVoice);
    library->setNPC(ghost);

    auto foyerPuzzle = std::make_shared<Puzzle>(
        "Riddle: 'I'm light as a feather, yet the strongest man can't hold me for more than 5 minutes. What am I?'",
        "breath");
    auto libraryPuzzle = std::make_shared<Puzzle>(
        "Combination: 'Three explorers set out on an adventure. Each carries items in multiples of five: What are they'",
        "5 10 15");
    auto basementPuzzle = std::make_shared<Puzzle>(
        "Riddle: 'The more of me you take, the more you leave behind. What am I?'",
        "footsteps");

    foyer->setPuzzle(foyerPuzzle);
    library->setPuzzle(libraryPuzzle);
    basement->setPuzzle(basementPuzzle);

    foyer->setExit("north", library);
    library->setExit("south", foyer);
    library->setExit("down", basement);

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
              << "  quit          - Exit the game.\n"
              << "  help          - Display the game instructions.\n";
}

void Game::start() {
    displayInstructions();

    while (!isGameOver) {
        std::cout << "> ";
        std::string command;
        std::getline(std::cin, command);
        processCommand(command);

        if (checkWinCondition()) {
            std::cout << "The amulet glows brightly, banishing the darkness. You have restored the manor!\n";
            isGameOver = true;
        }
    }

    std::cout << "Thank you for playing! Goodbye!\n";
}

void Game::processCommand(const std::string& command) {
    auto currentRoom = player->getCurrentRoom();
    std::string action, argument;
    size_t spaceIndex = command.find(' ');

    if (spaceIndex != std::string::npos) {
        action = command.substr(0, spaceIndex); // Extract action (e.g., "take", "move")
        argument = command.substr(spaceIndex + 1); // Extract argument (e.g., "torch")
    } else {
        action = command; // Command without argument (e.g., "look", "inventory")
    }

    // Convert action and argument to lowercase for consistency
    std::transform(action.begin(), action.end(), action.begin(), ::tolower);
    std::transform(argument.begin(), argument.end(), argument.begin(), ::tolower);

    if (action == "look") {
        currentRoom->describe();
    } 
    else if (action == "move") {
        if (!argument.empty()) {
            auto nextRoom = currentRoom->getExit(argument);
            if (nextRoom) {
                if (!currentRoom->isPuzzleSolved()) {
                    std::cout << "The room is locked. Solve the puzzle first to proceed.\n";
                } else {
                    player->move(argument);
                }
            } else {
                std::cout << "There is no exit in that direction.\n";
            }
        } else {
            std::cout << "Specify a direction to move (e.g., 'move north').\n";
        }
    } 
    else if (action == "take") {
        if (!argument.empty()) {
            auto item = currentRoom->findItem(argument);
            if (item) {
                player->pickUp(item);
                currentRoom->removeItem(item);
                std::cout << "You picked up the " << item->getName() << ".\n";
            } else {
                std::cout << "There is no " << argument << " here.\n";
            }
        } else {
            std::cout << "Specify an item to take (e.g., 'take torch').\n";
        }
    } 
    else if (action == "drop") {
        if (!argument.empty()) {
            auto item = player->findItemInInventory(argument);
            if (item) {
                player->dropItem(item);
                currentRoom->addItem(item);
                std::cout << "You dropped the " << item->getName() << " in the room.\n";
            } else {
                std::cout << "You don't have " << argument << " in your inventory.\n";
            }
        } else {
            std::cout << "Specify an item to drop (e.g., 'drop torch').\n";
        }
    } 
    else if (action == "use") {
        if (!argument.empty()) {
            auto item = player->findItemInInventory(argument);
            if (item) {
                item->use();
                // Add specific game logic for "using" items (e.g., unlocking rooms, scaring NPCs, etc.)
                if (argument == "torch" && currentRoom->getNPC() && currentRoom->getNPC()->getName() == "Ghost") {
                    std::cout << "The ghost is scared by the torch and vanishes!\n";
                    currentRoom->setNPC(nullptr);
                }
            } else {
                std::cout << "You don't have " << argument << " in your inventory.\n";
            }
        } else {
            std::cout << "Specify an item to use (e.g., 'use torch').\n";
        }
    } 
    else if (action == "solve") {
        auto puzzle = currentRoom->getPuzzle();
        if (puzzle && !puzzle->getIsSolved()) {
            std::cout << puzzle->getDescription() << "\nAnswer: ";
            std::string answer;
            std::getline(std::cin, answer);
            std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
            if (puzzle->attemptSolution(answer)) {
                std::cout << "You solved the puzzle!\n";
            } else {
                std::cout << "That's not correct.\n";
            }
        } else {
            std::cout << "There is no puzzle to solve here.\n";
        }
    } 
    else if (action == "inventory") {
        const auto& inventory = player->getInventory();
        if (inventory.empty()) {
            std::cout << "Your inventory is empty.\n";
        } else {
            std::cout << "Your inventory contains:\n";
            for (const auto& item : inventory) {
                std::cout << "- " << item->getName() << "\n";
            }
        }
    } 
    else if (action == "help") {
        displayInstructions();
    } 
    else if (action == "quit") {
        isGameOver = true;
    } 
    else {
        std::cout << "Unknown command. Type 'help' for a list of commands.\n";
    }
}


bool Game::checkWinCondition() const {
    auto amulet = player->findItemInInventory("amulet");
    return amulet != nullptr;
}
