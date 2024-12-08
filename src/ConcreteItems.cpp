#include "ConcreteItems.hpp"

// Flashlight Implementation
Flashlight::Flashlight() {
    name = "Flashlight";
    description = "A flashlight to help you see in the dark.";
}
void Flashlight::use() {
    std::cout << "The flashlight illuminates the room.\n";
}

// Key Implementation
Key::Key(const std::string& keyName) {
    name = keyName;
    description = "A small key, possibly for a door.";
}
void Key::use() {
    std::cout << "The key unlocks a door.\n";
}

// Amulet Implementation
Amulet::Amulet() {
    name = "Amulet";
    description = "An ancient amulet that wards off spirits.";
}
void Amulet::use() {
    std::cout << "The amulet glows, protecting you from harm.\n";
}




