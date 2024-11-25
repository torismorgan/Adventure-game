
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

void Game::processCommand(const std::string& command){

}


bool Game::checkWinCondition(){

}

void Game::start(){

}

void Game::endGame(){}


//GameDisplay class


void GameDisplay::displayWelcomeMessage(){}


void GameDisplay::displayGoodbyeMessage(){}

void GameDisplay::displayRoomDescription(Room* room){}

void GameDisplay::displayError(const std::string& error){}
