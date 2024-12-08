#ifndef NPC_HPP
#define NPC_HPP

#include <string>
#include <iostream>

class NPC {
protected:
    std::string name;
    std::string dialogue;

public:
    NPC(const std::string& npcName, const std::string& npcDialogue)
        : name(npcName), dialogue(npcDialogue) {}

    virtual ~NPC() = default;

    // Getters
    std::string getName() const { return name; }
    std::string getDialogue() const { return dialogue; }

    // Interaction method
    virtual void interact() {
        std::cout << dialogue << std::endl;
    }
};

#endif // NPC_HPP
