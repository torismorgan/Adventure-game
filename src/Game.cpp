
#include "game.hpp"
#include <iostream>

//Game Class
Game::Game() : isGameOver(false) {
// Initialize rooms (you can later delegate this to a RoomManager if needed)
Room* foyer = new Room("You are in a small foyer. There is a door to the north.");
Room* library = new Room("You are in a grand library. Books are stacked high.");
Room* basement = new Room("You are in a dark basement. It smells damp.");

// Set exits
foyer->setExit("north", library);
library->setExit("south", foyer);
library->setExit("down", basement);
basement->setExit("up", library);

// Add to room map
rooms["foyer"] = foyer;
rooms["library"] = library;
rooms["basement"] = basement;

// Set starting room
player.setCurrentRoom(foyer);
}

Game::~Game() {
// Clean up dynamically allocated rooms
for (auto& pair : rooms) {
delete pair.second;
}
}

void Game::processCommand(const std::string& command) {
if (command == "look") {
GameDisplay::displayRoomDescription(player.getCurrentRoom());
} else if (command.find("move") == 0) {
std::string direction = command.substr(5); // Extract direction
if (!player.move(direction)) {
GameDisplay::displayError("You can't move that way!");
}
} else if (command == "help") {
GameDisplay::displayHelp();
} else if (command == "quit") {
isGameOver = true;
} else {
GameDisplay::displayError("Invalid command. Type 'help' for a list of commands.");
}
}

bool Game::checkWinCondition() {
// Example condition: Player must reach the basement to win
if (player.getCurrentRoom()->getDescription() == "You are in a dark basement. It smells damp.") {
return true;
}
return false;
}

void Game::start() {
GameDisplay::displayWelcomeMessage();

while (!isGameOver) {
std::cout << "> ";
std::string command;
std::getline(std::cin, command);

processCommand(command);

if (checkWinCondition()) {
std::cout << "Congratulations! You have achieved your goal and won the game!" << std::endl;
isGameOver = true;
}
}

GameDisplay::displayGoodbyeMessage();
}

