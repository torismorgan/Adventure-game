#ifndef CONCRETENPCS_HPP
#define CONCRETENPCS_HPP

#include "NPC.hpp"
#include <iostream>

// Ghost
 class Ghost : public NPC {
public:
    Ghost();
    void interact() override;
    void hauntPlayer();
};

// Whispering Voice
 class WhisperingVoice : public NPC {
public:
    WhisperingVoice();
    void interact() override;
    std::string giveHint() const;
};

#endif


