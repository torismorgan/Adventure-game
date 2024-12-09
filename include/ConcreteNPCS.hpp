#ifndef CONCRETENPCS_HPP
#define CONCRETENPCS_HPP

#include "NPC.hpp"
#include <string>

class WhisperingVoice : public NPC {
public:
    WhisperingVoice();
    void interact() override;
};

class Ghost : public NPC {
public:
    Ghost();
    void interact() override;
};

#endif // CONCRETENPC_HPP

