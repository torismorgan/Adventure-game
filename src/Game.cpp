#include "Game.hpp"
#include "ConcreteItems.hpp"
#include "ConcreteNPCS.hpp"
#include <iostream>
#include <algorithm>

// Constructor
Game::Game() : isGameOver(false) {
    setupGame();
}

// Destructor
Game::~Game() = default;

// Set up the game world
void Game::setupGame() {
    // Create items
    auto torch = std::make_shared<Torch>();
    auto keyItem = std::make_shared<Key>();
    auto amulet = std::make_shared<Amulet>();

    // Create rooms
    auto foyer = std::make_shared<Room>("A dimly lit foyer with a whispering voice.");
    auto library = std::make_shared<Room>("A grand library filled with dusty books and a ghost.");
    auto basement = std::make_shared<Room>("A damp, dark basement with a locked chest.");

    // Add items to rooms
    foyer->addItem(torch);
    library->addItem(keyItem);

    // Create NPCs
    auto whisperingVoice = std::make_shared<WhisperingVoice>();
    auto ghost = std::make_shared<Ghost>();

    foyer->setNPC(whisperingVoice);
    library->setNPC(ghost);

    // Add puzzles
    auto foyerPuzzle = std::make_shared<Puzzle>(
        "Riddle: 'I'm light as a feather, yet the strongest man can't hold me for more than 5 minutes. What am I?'",
        "breath");
    auto libraryPuzzle = std::make_shared<Puzzle>(
        "Combination: 'Three explorers set out on an adventure...'",
        "5 10 15");
    auto basementPuzzle = std::make_shared<Puzzle>(
        "Riddle: 'The more of me you take, the more you leave behind. What am I?'",
        "footsteps");

    foyer->setPuzzle(foyerPuzzle);
    library->setPuzzle(libraryPuzzle);
    basement->setPuzzle(basementPuzzle);

    // Set room exits
    foyer->setExit("north", library);
    library->setExit("south", foyer);
    library->setExit("down", basement);

    // Set the player's starting room
    player = std::make_shared<Player>(foyer);
}

// Display game instructions
void Game::displayInstructions() const {
    std::cout << "Your goal is to find the amulet and restore the manor.\n"
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

// Start the game
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

// Process player commands
void Game::processCommand(std::string command) {
    auto currentRoom = player->getCurrentRoom();
    std::transform(command.begin(), command.end(), command.begin(), ::tolower); // Convert command to lowercase

    if (command == "look") {
        currentRoom->describe();
        auto npc = currentRoom->getNPC();
        if (npc) {
            npc->interact();
        }
    } else if (command.find("move") == 0) {
        std::string direction = command.substr(5); // Extract direction
        auto nextRoom = currentRoom->getExit(direction);
        if (nextRoom) {
            if (!currentRoom->isPuzzleSolved()) {
                std::cout << "You must solve the puzzle here before moving to the next room.\n";
                return;
            }
            player->move(direction);
        } else {
            std::cout << "There is no exit in that direction.\n";
        }
    } else if (command.find("take") == 0) {
        std::string itemName = command.substr(5); // Extract item name
        auto item = currentRoom->findItem(itemName);
        if (item) {
            player->pickUp(item);
            currentRoom->removeItem(item);
            std::cout << "You picked up the " << itemName << ".\n";
        } else {
            std::cout << "There is no " << itemName << " here.\n";
        }
    } else if (command.find("drop") == 0) {
        std::string itemName = command.substr(5); // Extract item name
        auto item = player->findItemInInventory(itemName);
        if (item) {
            player->dropItem(item);
            currentRoom->addItem(item);
            std::cout << "You dropped the " << itemName << ".\n";
        } else {
            std::cout << "You don't have " << itemName << " in your inventory.\n";
        }
    } else if (command.find("use") == 0) {  // Check if the command is to use an item
        std::string itemName = command.substr(4); // Extract item name
        auto item = player->findItemInInventory(itemName);
        if (item) {
            item->use();
        } else {
            std::cout << "You don't have " << itemName << " in your inventory.\n";
        }
    } else if (command == "solve") {
        auto puzzle = currentRoom->getPuzzle();
        if (puzzle && !puzzle->getIsSolved()) {
            std::cout << puzzle->getDescription() << "\nAnswer: ";
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
    } else if (command == "inventory") {
        player->showInventory();
    } else if (command == "quit") {
        isGameOver = true;
    } else {
        std::cout << "Unknown command. Type 'help' for a list of commands.\n";
    }
}


// Check if the player has won the game
bool Game::checkWinCondition() {
    auto amulet = player->findItemInInventory("amulet");
    return amulet != nullptr;
}

