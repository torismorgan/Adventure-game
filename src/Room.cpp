#include "Room.h"
#include <algorithm>

Room::Room(const std::string& desc) : description(desc) {}

void Room::enter() {
// Base implementation - can be overridden by derived classes
}

std::string Room::getDescription() const {
    return description;
}

void Room::addItem(std::shared_ptr<Item> item) {
    if (item) {
        items.push_back(item);
    }
}

void Room::removeItem(std::shared_ptr<Item> item) {
    auto it = std::find(items.begin(), items.end(), item);
    if (it != items.end()) {
        items.erase(it);
    }
}

std::shared_ptr<Room> Room::getExit(const std::string& direction) const {
    auto it = exits.find(direction);
    return (it != exits.end()) ? it->second : nullptr;
}

void Room::setExit(const std::string& direction, std::shared_ptr<Room> room) {
    if (room) {
        exits[direction] = room;
    }
}

const std::vector<std::shared_ptr<Item>>& Room::getItems() const {
    return items;
}

void Room::setPuzzle(std::shared_ptr<Puzzle> newPuzzle) {
    puzzle = newPuzzle;
}

std::shared_ptr<Puzzle> Room::getPuzzle() const {
    return puzzle;
}

bool Room::hasExit(const std::string& direction) const {
    return exits.find(direction) != exits.end();
}
