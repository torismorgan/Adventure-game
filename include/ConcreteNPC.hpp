#ifndef CONCRETENPCS_H
#define CONCRETENPCS_H

#include "NPC.h"

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


#endif // NPC_H