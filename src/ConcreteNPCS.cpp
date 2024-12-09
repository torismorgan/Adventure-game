#include "ConcreteNPCS.hpp"
#include <iostream>

// Whispering Voice Implementation
WhisperingVoice::WhisperingVoice() {
    name = "Whispering Voice";
    dialogue = "A faint voice whispers: 'Focus on the air, and the answer will come to you.'";
}

void WhisperingVoice::interact() {
    std::cout << dialogue << std::endl;
}

// Ghost Implementation
Ghost::Ghost() {
    name = "Ghost";
    dialogue = "The ghost looms before you, blocking your path.";
}

void Ghost::interact() {
    std::cout << dialogue << std::endl;
}
