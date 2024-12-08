#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <string>

class Puzzle {
private:
    std::string description;
    std::string solution;
    bool isSolved;

public:
    Puzzle(const std::string& desc, const std::string& sol);

    std::string getDescription() const;
    bool attemptSolution(const std::string& playerInput);
    bool getIsSolved() const;
    std::string getHint() const;

};

#endif // PUZZLE_HPP
