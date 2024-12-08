#include "Room.hpp"
#include <algorithm>
#include <iostream>

Room::Room(const std::string& desc) : description(desc) {}

std::string Room::getDescription() const {
    return description;
}

const std::vector<std::shared_ptr<Item>>& Room::getItems() const {
    return items;
}

void Room::addItem(std::shared_ptr<Item> item) {
    if (item) items.push_back(item);
}

void Room::removeItem(std::shared_ptr<Item> item) {
    auto it = std::find_if(items.begin(), items.end(),
        [&](const std::shared_ptr<Item>& i) {
            return i->getName() == item->getName();
        });
    if (it != items.end()) {
        items.erase(it);
    }
}

void Room::setExitWithDoor(const std::string& direction, std::shared_ptr<Room> room, std::shared_ptr<Door> door) {
    exits[direction] = {room, door};
}

std::shared_ptr<Room> Room::getExit(const std::string& direction) const {
    auto it = exits.find(direction);
    if (it != exits.end()) return it->second.first;
    return nullptr;
}

bool Room::isDoorLocked(const std::string& direction) const {
    auto it = exits.find(direction);
    if (it != exits.end() && it->second.second) return it->second.second->getIsLocked();
    return false;
}

