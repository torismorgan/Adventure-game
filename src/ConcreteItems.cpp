#include "ConcreteItems.hpp"
#include <iostream>

Flashlight::Flashlight() {
    name = "Flashlight";
    description = "A flashlight to help you see in the dark.";
}

void Flashlight::use() {
    std::cout << "The flashlight illuminates the room.\n";
}

Key::Key() {
    name = "Key";
    description = "A small key, possibly for a door.";
}

void Key::use() {
    std::cout << "The key unlocks a door.\n";
}

Amulet::Amulet() {
    name = "Amulet";
    description = "An ancient amulet that wards off spirits.";
}

void Amulet::use() {
    std::cout << "The amulet glows, protecting you from harm.\n";
}

Map::Map() {
    name = "Map";
    description = "A map that shows the layout of the mansion.";
}

void Map::use() {
    std::cout << "The map displays the mansion layout.\n";
}

Book::Book() {
    name = "Book";
    description = "A dusty old book with a ciphered message.";
}

void Book::use() {
    std::cout << "The book reveals a hidden message.\n";
}


