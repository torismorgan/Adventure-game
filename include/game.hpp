#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <map>

class Game{
private:
    Player player; //the player object
    std::map<std::string, Room*> rooms; //All rooms in the game
    bool isGameOver; //tracks if the game has ended

    void setupRooms(); //imitializes all the rooms
    void processCommand(const std::string command); //handles player input
    void displayWelcomeMessage();
    void displayHelp();

public:
    Game();     //constructor
    Game~();    //destructor

    void start();   //starts the game;loop
    bool checkWinCondition(); //checks if the game is won
    void endGame();

}



#endif