#include "GameDisplay.hpp"
#include <iostream>
#include <string>

// Welcome Message
void GameDisplay::displayWelcomeMessage() {
std::cout << "\nWelcome to the Adventure Game!\n";
std::cout << "Explore, solve puzzles, and escape the mysterious manor.\n";
std::cout << "Type 'help' to see the list of commands.\n\n";
}

// Goodbye Message
void GameDisplay::displayGoodbyeMessage() {
std::cout << "\nThank you for playing! Goodbye!\n";
}

// Room Description
void GameDisplay::displayRoomDescription(Room* room) {
if (room) {
room->describe();
} else {
std::cout << "You are lost. There seems to be no room here.\n";
}
}

// Error Messages
void GameDisplay::displayError(const std::string& error) {
std::cout << "Error: " << error << "\n";
}

// Help / Instructions
void GameDisplay::displayHelp() {
std::cout << "\n=== Game Instructions ===\n";
std::cout << "Welcome to the Adventure Game!\n";
std::cout << "Your goal is to explore, collect items, and solve puzzles.\n";
std::cout << "\nAvailable Commands:\n";
std::cout << "1. look - Look around the room.\n";
std::cout << "2. move [dir] - Move to another room (e.g., 'move north').\n";
std::cout << "3. take [item] - Pick up an item (e.g., 'take Key').\n";
std::cout << "4. use [item] - Use an item from your inventory.\n";
std::cout << "5. inventory - View your inventory.\n";
std::cout << "6. quit - Exit the game.\n";
std::cout << "\nHints:\n";
std::cout << "- Use 'look' to check the room for items and exits.\n";
std::cout << "- Use 'take' to collect important items.\n";
std::cout << "- Pay attention to room descriptions for clues.\n";
std::cout << "==========================\n\n";
}

// Winning Message
void GameDisplay::displayWinMessage() {
std::cout << "\nCongratulations! You have successfully escaped the manor!\n";
std::cout << "Well done, adventurer!\n";
}
