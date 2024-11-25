#ifndef CONCRETENPC_HPP
#define CONCRETENPC_HPP

#include "NPC.hpp"

class Ghost : public NPC {
public:
    Ghost();
    void interact() override;
    void hauntPlayer();
};

class WhisperingVoice : public NPC {
public:
    WhisperingVoice();
    void interact() override;
    std::string giveHint() const;
};

#endif // CONCRETENPCS_H
