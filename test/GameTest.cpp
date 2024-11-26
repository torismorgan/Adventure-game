/*#include "GameClass.hpp"
#include "gtest/gtest.h"

// Test the constructor
TEST(GameTest, Constructor) {
Game game;
ASSERT_FALSE(game.checkWinCondition()); // Win condition should be false initially
}

// Test processing a valid command
TEST(GameTest, ProcessValidCommand) {
Game game;
game.processCommand("look");
// No crashes or invalid states means the test passes
SUCCEED();
}

// Test processing an invalid command
TEST(GameTest, ProcessInvalidCommand) {
Game game;
game.processCommand("invalid_command");
// No crashes or unexpected behavior means success
SUCCEED();
}

// Test win condition
TEST(GameTest, CheckWinCondition) {
Game game;
game.processCommand("move north");
ASSERT_FALSE(game.checkWinCondition()); // Player hasn't won yet
}
