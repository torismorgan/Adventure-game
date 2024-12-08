#include "Room.hpp"
#include <algorithm>
#include <iostream>

Room::Room(const std::string& desc) : description(desc) {}

std::string Room::getDescription() const {
    return description;
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

const std::vector<std::shared_ptr<Item>>& Room::getItems() const {
    return items;
}

void Room::setExit(const std::string& direction, std::shared_ptr<Room> room) {
    exits[direction] = std::make_shared<Door>(room);
}

std::shared_ptr<Room> Room::getExit(const std::string& direction) const {
    auto it = exits.find(direction);
    if (it != exits.end() && !(it->second->isLocked())) {
        return it->second->getConnectedRoom();
    }
    return nullptr;
}

void Room::lockExit(const std::string& direction, std::shared_ptr<Key> key) {
    if (exits.find(direction) != exits.end()) {
        exits[direction]->lock(key);
    }
}

bool Room::unlockExit(const std::string& direction, std::shared_ptr<Key> key) {
    auto it = exits.find(direction);
    if (it != exits.end()) {
        return it->second->unlock(key);
    }
    return false;
}



