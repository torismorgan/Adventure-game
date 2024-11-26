/*#include "Puzzle.hpp"
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

// Test attemptSolution with correct and incorrect answers
TEST(PuzzleTest, AttemptSolutionChecksAnswersCorrectly) {
Puzzle puzzle("I'm tall when I'm young, and I'm short when I'm old. What am I?", "candle");

EXPECT_FALSE(puzzle.getIsSolved()); // Initially unsolved
EXPECT_FALSE(puzzle.attemptSolution("matchstick")); // Incorrect answer
EXPECT_FALSE(puzzle.getIsSolved()); // Still unsolved
EXPECT_TRUE(puzzle.attemptSolution("candle")); // Correct answer
EXPECT_TRUE(puzzle.getIsSolved()); // Now solved
}

// Test getIsSolved
TEST(PuzzleTest, GetIsSolvedReflectsPuzzleState) {
Puzzle puzzle("What has a heart but no other organs?", "deck of cards");
EXPECT_FALSE(puzzle.getIsSolved()); // Initially unsolved
puzzle.attemptSolution("deck of cards");
EXPECT_TRUE(puzzle.getIsSolved()); // Solved after correct answer
}
