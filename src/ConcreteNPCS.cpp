#include "ConcreteNPCS.hpp"
#include <iostream>

// Whispering Voice Implementation
WhisperingVoice::WhisperingVoice()
    : NPC("Whispering Voice", "A faint voice whispers: 'Focus on the air, and the answer will come to you.'") {}

void WhisperingVoice::interact() {
    std::cout << dialogue << std::endl;
}

// Ghost Implementation
Ghost::Ghost()
    : NPC("Ghost", "The ghost looms before you, blocking your path.") {}

void Ghost::interact() {
    std::cout << dialogue << std::endl;
}

