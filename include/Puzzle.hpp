#ifndef PUZZLE_HPP
#define PUZZLE_HPP
#include <cstddef>
#include <string>

class Puzzle {
 private:
  std::string description;  // Description of the puzzle
  std::string solution;     // Correct solution for the puzzle
  bool isSolved;            // Tracks if the puzzle has been solved

 public:
  // Constructor
  Puzzle(const std::string& description, const std::string& solution);

  // Getter for the puzzle's hint
  std::string getHint() const;

  // Method to attempt solving the puzzle
  bool attemptSolution(const std::string& playerInput);

  // Getter for isSolved
  bool getIsSolved() const;

  // Getter for the description
  std::string getDescription() const;
};

#endif
