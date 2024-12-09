#ifndef CONCRETENPCS_HPP
#define CONCRETENPCS_HPP

#include "NPC.hpp"

// Whispering Voice NPC
class WhisperingVoice : public NPC {
public:
    WhisperingVoice();
    void interact() override {
        std::cout << "The Whispering Voice murmurs: 'Focus on the air, and the answer will come to you.'\n";
    }
};


// Ghost NPC
class Ghost : public NPC {
public:
    Ghost();
    void interact() override;
    bool isAfraidOfTorch() const { return true; }
};


#endif // CONCRETENPCS_HPP
