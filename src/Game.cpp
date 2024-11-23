
#include "game.hpp"
#include <iostream>

//Game Class
Game:: Game(): isGameOver(){

}

Game:: ~Game(){

}

void Game::processCommand(const std::string& command){

}


bool Game::checkWinCondition(){

}

void Game::start(){

}

void Game::endGame(){}


//GameDisplay class


void GameDisplay::displayWelcomeMessage(){}


void GameDisplay::displayGoodbyeMessage(){}

void GameDisplay::displayRoomDescription(Room* room){}

void GameDisplay::displayError(const std::string& error){}
