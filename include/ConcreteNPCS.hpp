#ifndef CONCRETENPCS_HPP
#define CONCRETENPCS_HPP

#include "NPC.hpp"

// Whispering Voice NPC
class WhisperingVoice : public NPC {
public:
    WhisperingVoice() 
        : NPC("Whispering Voice", "A faint whisper echoes: 'The library holds the key...'") {}

    void interact() override {
        std::cout << "The Whispering Voice murmurs: 'Puzzles will guide you to the light.'\n";
    }
};

// Ghost NPC
class Ghost : public NPC {
public:
    Ghost() 
        : NPC("Ghost", "The ghost blocks your path, its chilling gaze piercing through you.") {}

    void interact() override {
        std::cout << "The ghost stares at you silently. It looks like it fears fire.\n";
    }
};

#endif // CONCRETENPCS_HPP
