#include "Room.hpp"
#include <iostream>
#include <algorithm>

Room::Room(const std::string& desc) : description(desc) {}

void Room::describe() const {
    std::cout << description << std::endl;
    if (npc) {
        std::cout << "You see " << npc->getName() << " here.\n";
    }
    if (puzzle && !puzzle->getIsSolved()) {
        std::cout << "There is a puzzle: " << puzzle->getDescription() << "\n";
    }
    std::cout << "Items in the room:\n";
    for (const auto& item : items) {
        std::cout << "- " << item->getName() << "\n"; // Debug: print item names
    }
}


void Room::addItem(std::shared_ptr<Item> item) {
    items.push_back(item);
}

void Room::removeItem(std::shared_ptr<Item> item) {
    items.erase(std::remove(items.begin(), items.end(), item), items.end());
}

std::shared_ptr<Item> Room::findItem(const std::string& itemName) const {
    std::string normalizedItemName = itemName;
    std::transform(normalizedItemName.begin(), normalizedItemName.end(), normalizedItemName.begin(), ::tolower);

    for (const auto& item : items) {
        std::string normalizedStoredName = item->getName();
        std::transform(normalizedStoredName.begin(), normalizedStoredName.end(), normalizedStoredName.begin(), ::tolower);

        if (normalizedStoredName == normalizedItemName) {
            return item; // Return the matching item
        }
    }
    return nullptr; // Return nullptr if no match is found
}


void Room::setExit(const std::string& direction, std::shared_ptr<Room> room) {
    exits[direction] = room;
}

std::shared_ptr<Room> Room::getExit(const std::string& direction) const {
    auto it = exits.find(direction);
    return (it != exits.end()) ? it->second : nullptr;
}

// Implementation of getDescription
std::string Room::getDescription() const {
    return description;
}

