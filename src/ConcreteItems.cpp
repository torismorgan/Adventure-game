#include "ConcreteItems.hpp"
#include <iostream>

Torch::Torch() {
    name = "Torch";
    description = "A small torch that lights the way.";
}

void Torch::use() {
    std::cout << "The torch flickers and lights the room.\n";
}

Amulet::Amulet() {
    name = "Amulet";
    description = "The amulet glows with a mysterious power.";
}

void Amulet::use() {
    std::cout << "The amulet pulses with energy, dispelling darkness.\n";
}




