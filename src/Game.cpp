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

void Game::processCommand(std::string command) {
    auto currentRoom = player->getCurrentRoom();
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);

    if (command == "look") {
        currentRoom->describe();
    } else if (command.find("move") == 0) {
        std::string direction = command.substr(5);
        auto nextRoom = currentRoom->getExit(direction);

        if (!nextRoom) {
            std::cout << "There is no exit in that direction.\n";
        } else if (currentRoom->getDescription().find("locked") != std::string::npos && !currentRoom->isPuzzleSolved()) {
            std::cout << "The room is locked. Solve the puzzle to proceed.\n";
        } else if (currentRoom->getNPC() && currentRoom->getNPC()->getName() == "Ghost") {
            std::cout << "The ghost blocks your way! Use something to scare it away.\n";
        } else {
            player->move(direction);
        }

         } else if (command == "help") {
        // Display the help message
        displayInstructions();
    } else if (command.find("take") == 0) {
        std::string itemName = command.substr(5);
        auto item = currentRoom->findItem(itemName);
        if (item) {
            player->pickUp(item);
            currentRoom->removeItem(item);
            std::cout << "You picked up the " << item->getName() << ".\n";
        } else {
            std::cout << "There is no " << itemName << " here.\n";
        }
    } else if (command.find("use torch") != std::string::npos) {
        auto npc = currentRoom->getNPC();
        if (npc && npc->getName() == "Ghost") {
            std::cout << "You used the torch! The ghost flees in terror!\n";
            currentRoom->setNPC(nullptr);
        } else {
            std::cout << "The torch flickers but has no effect here.\n";
        }
    } else if (command == "solve") {
        auto puzzle = currentRoom->getPuzzle();
        if (puzzle && !puzzle->getIsSolved()) {
            std::cout << puzzle->getDescription() << "\nAnswer: ";
            std::string answer;
            std::getline(std::cin, answer);
            if (puzzle->attemptSolution(answer)) {
                std::cout << "You solved the puzzle! The room is now unlocked.\n";
            } else {
                std::cout << "That's not correct.\n";
            }
        } else {
            std::cout << "There is no puzzle to solve here.\n";
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

bool Game::checkWinCondition() const {
    auto amulet = player->findItemInInventory("amulet");
    return amulet != nullptr;
}
