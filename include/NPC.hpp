#ifndef NPC_H
#define NPC_H

#include <string>

class NPC {
protected:
    std::string name;
    std::string dialogue;

public:
    virtual ~NPC() = default;
    virtual void interact() = 0;
    std::string getName() const;
    std::string getDialogue() const;
};