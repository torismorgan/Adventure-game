#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <map>

class Game{
    private:
    Player player; //the player object
    std::map<std::string, Room*> rooms; //All rooms in the game
    bool isGameOver; //tracks if the game has ended
}



#endif