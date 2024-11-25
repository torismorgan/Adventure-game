
11:08

#include "Puzzle.hpp"

// Constructor
Puzzle::Puzzle(const std::string& description, const std::string& solution)
: description(description), solution(solution), isSolved(false) {}

// Getter for the puzzle's description
std::string Puzzle::getDescription() const {
return description;
}

// Getter for the puzzle's hint
std::string Puzzle::getHint() const {
// Provide a simple hint (for example, the first letter of the solution)
if (!isSolved) {
return "Hint: The solution starts with '" + solution.substr(0, 1) + "'.";
}
return "The puzzle is already solved.";
}

// Method to attempt solving the puzzle
bool Puzzle::attemptSolution(const std::string& playerInput) {
if (playerInput == solution) {
isSolved = true;
return true; // Solution is correct
}
return false; // Solution is incorrect
}

// Getter for isSolved
bool Puzzle::getIsSolved() const {
return isSolved;
}
