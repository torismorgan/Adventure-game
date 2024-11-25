#include "Puzzle.hpp"
#include "gtest/gtest.h"

// Test the constructor
TEST(PuzzleTest, ConstructorInitializesCorrectly) {
Puzzle puzzle("What has keys but can't open locks?", "keyboard");
EXPECT_EQ(puzzle.getDescription(), "What has keys but can't open locks?");
EXPECT_FALSE(puzzle.getIsSolved());
}


// Test getDescription
TEST(PuzzleTest, GetDescriptionReturnsCorrectDescription) {
Puzzle puzzle("A tricky puzzle awaits.", "answer");
EXPECT_EQ(puzzle.getDescription(), "A tricky puzzle awaits.");
}

// Test getHint
TEST(PuzzleTest, GetHintProvidesCorrectHint) {
Puzzle puzzle("What has to be broken before you can use it?", "egg");
EXPECT_EQ(puzzle.getHint(), "Hint: The solution starts with 'e'.");
puzzle.attemptSolution("wrong answer");
EXPECT_EQ(puzzle.getHint(), "Hint: The solution starts with 'e'.");
puzzle.attemptSolution("egg");
EXPECT_EQ(puzzle.getHint(), "The puzzle is already solved.");
}
