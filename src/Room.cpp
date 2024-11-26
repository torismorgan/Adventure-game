#include "Room.hpp"
#include <iostream>
#include <algorithm>

Room::Room(const std::string& desc) : description(desc) {}

std::string Room::getDescription() const {
    return description;
}

void Room::describe() const {
    std::cout << description << "\n";
}

void Room::enter() {
    std::cout << "You have entered: " << description << "\n";
}

void Room::addItem(std::shared_ptr<Item> item) {
    items.push_back(item);
}

void Room::removeItem(std::shared_ptr<Item> item) {
    auto it = std::find(items.begin(), items.end(), item);
    if (it != items.end()) {
        items.erase(it);
    }
}

void Room::setExit(const std::string& direction, std::shared_ptr<Room> room) {
    exits[direction] = room;
}

std::shared_ptr<Room> Room::getExit(const std::string& direction) const {
    auto it = exits.find(direction);
    return it != exits.end() ? it->second : nullptr;
}

const std::vector<std::shared_ptr<Item>>& Room::getItems() const {
    return items;
}



