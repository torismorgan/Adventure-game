#include "ConcreteNPC.hpp"
#include <iostream>

Ghost::Ghost() {
    name = "Ghost";
    dialogue = "A chilling whisper echoes, threatening your soul...";
}

void Ghost::interact() {
    std::cout << dialogue << "\n";
}

void Ghost::hauntPlayer() {
    std::cout << "The ghost overwhelms you. Game over...\n";
}

WhisperingVoice::WhisperingVoice() {
    name = "Whispering Voice";
    dialogue = "A voice whispers a hint from the shadows.";
}

void WhisperingVoice::interact() {
    std::cout << dialogue << "\n";
}

std::string WhisperingVoice::giveHint() const {
    return "The answer lies in the book you found...";
}