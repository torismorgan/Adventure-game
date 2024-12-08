#ifndef CONCRETEITEMS_HPP
#define CONCRETEITEMS_HPP

#include "Item.hpp"

// Flashlight Class
class Flashlight : public Item {
public:
    Flashlight() {
        name = "Flashlight";
        description = "A flashlight to help you see in the dark.";
    }
    void use() override {
        std::cout << "The flashlight illuminates the room.\n";
    }
};

// Key Class
class Key : public Item {
public:
    Key(const std::string& keyName) {
        name = keyName;
        description = "A small key, possibly for a door.";
    }
    void use() override {
        std::cout << "The key unlocks a door.\n";
    }
};

// Amulet Class
class Amulet : public Item {
public:
    Amulet() {
        name = "Amulet";
        description = "An ancient amulet that wards off spirits.";
    }
    void use() override {
        std::cout << "The amulet glows, protecting you from harm.\n";
    }
};

#endif // CONCRETEITEMS_HPP





