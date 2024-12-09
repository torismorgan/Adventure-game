#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include <memory>
#include <string>
#include "Room.hpp"
#include "Player.hpp"

class Game {
private:
    std::shared_ptr<Player> player;
    bool isGameOver;

    void setupGame();
    bool checkWinCondition() const;

public:
    Game();
    ~Game();
    void start();
    void processCommand(std::string command);
};

#endif // GAME_HPP



