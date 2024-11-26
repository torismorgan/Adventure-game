#ifndef NPC_HPP
#define NPC_HPP

#include <string>

class NPC {
protected:
    std::string name;
    std::string dialogue;

public:
    virtual ~NPC() = default;
    virtual void interact() = 0;

    std::string getName() const;         // Declaration only
    std::string getDialogue() const;    // Declaration only
};

#endif

