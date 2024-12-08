#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include <memory>
#include "Room.hpp"
#include "Player.hpp"

class Game {
private:
    std::map<std::string, std::shared_ptr<Room>> rooms;
    std::shared_ptr<Player> player;
    bool isGameOver;

    void setupGame();
    bool checkWinCondition();

public:
    Game();
   // ~Game();
    void start();
    void processCommand(const std::string& command);
    void displayInstructions() const; // Ensure this is declared
};

#endif // GAME_HPP



