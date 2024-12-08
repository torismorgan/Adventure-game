#include "Room.hpp"
#include <iostream>
#include <algorithm>

Room::Room(const std::string& description) : description(description) {}

void Room::describe() const {
    std::cout << description << "\n";
    if (!items.empty()) {
        std::cout << "Items in the room:\n";
        for (const auto& item : items) {
            std::cout << "- " << item->getName() << "\n";
        }
    }
    if (!exits.empty()) {
        std::cout << "Exits:\n";
        for (const auto& exit : exits) {
            std::cout << "- " << exit.first << "\n";
        }
    }
}

void Room::addItem(std::shared_ptr<Item> item) {
    items.push_back(item);
}

void Room::removeItem(std::shared_ptr<Item> item) {
    items.erase(std::remove(items.begin(), items.end(), item), items.end());
}

std::vector<std::shared_ptr<Item>>& Room::getItems() {
    return items;
}

void Room::setExit(const std::string& direction, std::shared_ptr<Room> room) {
    exits[direction] = std::make_shared<Door>(false, room);
}

void Room::lockExit(const std::string& direction, std::shared_ptr<Flashlight> key) {
    if (exits.find(direction) != exits.end()) {
        exits[direction]->lock(key);
    }
}

std::shared_ptr<Door> Room::getExit(const std::string& direction) const {
    auto it = exits.find(direction);
    if (it != exits.end()) {
        return it->second;
    }
    return nullptr;
}





