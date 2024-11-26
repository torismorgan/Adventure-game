#ifndef GAMEDISPLAY_HPP
#define GAMEDISPLAY_HPP

#include <string>
#include "Room.hpp"

class GameDisplay {
 public:
void displayWelcomeMessage(); // Display welcome messages
void displayGoodbyeMessage(); // Display goodbye messages
void displayRoomDescription(Room* room); // Display current room description
void displayError(const std::string& error); // Display error messages
void displayHelp(); // Display game instructions
void displayWinMessage(); // Display a winning message
};

#endif // GAMEDISPLAY_HPP
