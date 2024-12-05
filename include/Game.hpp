#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include <memory>
#include <string>
#include "Room.hpp"
#include "ConcreteItems.hpp"
#include "Door.hpp"
#include "Player.hpp"

class Game {
private:
    std::map<std::string, std::shared_ptr<Room>> rooms;
    std::shared_ptr<Player> player;
    bool isGameOver = false;

    void processCommand(const std::string& command);

public:
    Game();
    ~Game() = default;
    void setupGame();
    void start();
};

#endif // GAME_HPP


