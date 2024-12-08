#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include <memory>
#include <string>
#include "Room.hpp"
#include "Player.hpp"
#include "GameDisplay.hpp"

class Game {
private:
    std::map<std::string, std::shared_ptr<Room>> rooms;
    std::shared_ptr<Player> player;
    bool isGameOver;

    void setupGame();
    bool checkWinCondition();
    void displayInstructions() const;

public:
    Game();
    ~Game();
    void start();
    void processCommand(const std::string& command);
};

#endif // GAME_HPP




