#include "GameClass.hpp"
#include "Room.hpp"
#include "Player.hpp"
#include <iostream>


// ------------------ Game Class ------------------

Game::Game() : isGameOver(false) {
// Initialize rooms
Room* foyer = new Room("You are in a small foyer. There is a door to the north.");
Room* library = new Room("You are in a grand library. Books are stacked high.");
Room* basement = new Room("You are in a dark basement. It smells damp.");

// Set exits
foyer->setExit("north", library);
library->setExit("south", foyer);
library->setExit("down", basement);
basement->setExit("up", library);f

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
if (command.length() <= 5) { // Check if direction is missing
GameDisplay::displayError("Move where? Please specify a direction.");
} else {
std::string direction = command.substr(5); // Extract direction
if (!player.move(direction)) {
GameDisplay::displayError("You can't move that way!");
}
}
} else if (command == "help") {
GameDisplay::displayHelp();
} else if (command == "quit") {
endGame();
} else {
GameDisplay::displayError("Invalid command. Type 'help' for a list of commands.");
}
}

bool Game::checkWinCondition() {
// Example condition: Winning happens if the player enters the basement
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
GameDisplay::displayWinMessage();
endGame();
}
}
}

void Game::endGame() {
isGameOver = true;
GameDisplay::displayGoodbyeMessage();
}




// ------------------ GameDisplay Class ------------------

void GameDisplay::displayWelcomeMessage() {
std::cout << "Welcome to the Adventure Game!" << std::endl;
std::cout << "Explore the rooms and achieve your goal. Type 'help' for a list of commands." << std::endl;
}

void GameDisplay::displayGoodbyeMessage() {
std::cout << "Thanks for playing! Goodbye!" << std::endl;
}

void GameDisplay::displayHelp() {
std::cout << "Available commands:" << std::endl;
std::cout << "- look: Look around the room." << std::endl;
std::cout << "- move [direction]: Move to another room." << std::endl;
std::cout << "- quit: Exit the game." << std::endl;
}

void GameDisplay::displayError(const std::string& error) {
std::cout << "Error: " << error << std::endl;
}

void GameDisplay::displayRoomDescription(Room* room) {
room->describe();
}

void GameDisplay::displayWinMessage() {
std::cout << "Congratulations! You have achieved your goal and won the game!" << std::endl;
}


