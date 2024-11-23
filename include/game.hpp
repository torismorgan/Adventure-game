#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <map>

class Game{
private:
    Player player; //the player object
    std::map<std::string, Room*> rooms; //All rooms in the game
    bool isGameOver; //tracks if the game has ended

    void processCommand(const std::string& command); //handles player input
    bool checkWinCondition(); //checks if the game is won

   
public:
    Game();     //constructor
    Game~();    //destructor

    void start();   //starts the game loop
    void endGame(); //ends game

};


class GameDisplay{
    public:
    void setupRooms(); //imitializes all the rooms
    
    void displayWelcomeMessage();     //display welcome messages
    void displayGoodbyeMessage();    //display goodbye messages
    void displayRoomDescription();   //displays the current room player is in and the description
    void displayError(const std::string& error);    //display error message

};
#endif