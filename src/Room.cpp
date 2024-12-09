#include "Room.hpp"
#include <iostream>
#include <algorithm>

Room::Room(const std::string& desc) : description(desc) {}

void Room::describe() const {
    std::cout << description << "\n";
    if (npc) {
        std::cout << "You see " << npc->getName() << " here.\n";
    }
    if (puzzle && !puzzle->getIsSolved()) {
        std::cout << "There is a puzzle: " << puzzle->getDescription() << "\n";
    }
    for (const auto& item : items) {
        std::cout << "- " << item->getName() << "\n";
    }
}

void Room::addItem(std::shared_ptr<Item> item) {
    items.push_back(item);
}

void Room::removeItem(std::shared_ptr<Item> item) {
    items.erase(std::remove(items.begin(), items.end(), item), items.end());
}

const std::vector<std::shared_ptr<Item>>& Room::getItems() const {
    return items;
}

void Room::setExit(const std::string& direction, std::shared_ptr<Room> room) {
    exits[direction] = room;
}

std::shared_ptr<Room> Room::getExit(const std::string& direction) const {
    auto it = exits.find(direction);
    return it != exits.end() ? it->second : nullptr;
}

void Room::setNPC(std::shared_ptr<NPC> newNpc) {
    npc = newNpc;
}

std::shared_ptr<NPC> Room::getNPC() const {
    return npc;
}

void Room::setPuzzle(std::shared_ptr<Puzzle> newPuzzle) {
    puzzle = newPuzzle;
}

std::shared_ptr<Puzzle> Room::getPuzzle() const {
    return puzzle;
}
std::string Room::getDescription() const {
    return description;
}

bool Room::isPuzzleSolved() const {
    return puzzle ? puzzle->getIsSolved() : true; // If no puzzle, consider it solved
}

void Room::setPuzzleSolved(bool solved) {
    if (puzzle) {
        puzzle->attemptSolution(""); // Automatically solve for transition logic
    }
}
bool Room::hasLockedChest() const {
    return description.find("chest") != std::string::npos;
}

void Room::unlockChest() {
    description += " The chest is now open, revealing the amulet.";
}
