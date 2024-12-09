#ifndef CONCRETENPC_HPP
#define CONCRETENPC_HPP

#include "NPC.hpp"
#include <string>

// Whispering Voice
class WhisperingVoice : public NPC {
public:
    WhisperingVoice();
    void interact() override;
};

// Ghost
class Ghost : public NPC {
public:
    Ghost();
    void interact() override;
};

#endif // CONCRETENPC_HPP
