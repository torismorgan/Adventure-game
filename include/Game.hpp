#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <map>
#include <memory>
#include "Player.hpp"
#include "Room.hpp"

class Game {
 private:
    std::shared_ptr<Player> player;
    std::map<std::string, std::shared_ptr<Room>> rooms;
    bool isGameOver;
    void setupGame();
    void processCommand(const std::string& command);

 public:
    Game();
    void start();
};

#endif
