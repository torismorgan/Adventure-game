#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include <memory>
#include <string>
#include "ConcreteItems.hpp"
#include "Player.hpp"
#include "GameDisplay.hpp" 

class Game {
 private:
  std::shared_ptr<Player> player;
  std::map<std::string, std::shared_ptr<Room>> rooms;
  bool isGameOver;
  void setupGame();  // Initializes rooms and items
  void processCommand(const std::string& command);  // Handles player input
  bool checkWinCondition();  // Checks if the player has won

 public:
  Game();   // Constructor
  ~Game();  // Destructor

  void start();  // Starts the game loop
};

#endif