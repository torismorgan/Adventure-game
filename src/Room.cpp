#include "Room.hpp"
#include <iostream>

Room::Room(const std::string& desc) : description(desc) {}

void Room::setExit(const std::string& direction, std::shared_ptr<Room> connectedRoom) {
    exits[direction] = std::make_shared<Door>(false, connectedRoom);
}

void Room::lockExit(const std::string& direction, std::shared_ptr<Key> key) {
    if (exits.find(direction) != exits.end()) {
        exits[direction]->lock(key);
    }
}

std::string Room::getDescription() const {
    return description;
}

std::vector<std::shared_ptr<Item>>& Room::getItems() {
    return items;
}

void Room::addItem(std::shared_ptr<Item> item) {
    items.push_back(item);
}

void Room::removeItem(std::shared_ptr<Item> item) {
    items.erase(std::remove(items.begin(), items.end(), item), items.end());
}

std::shared_ptr<Door> Room::getExit(const std::string& direction) {
    if (exits.find(direction) != exits.end()) {
        return exits[direction];
    }
    return nullptr;
}

void Room::describe() const {
    std::cout << description << "\n";
    if (!items.empty()) {
        std::cout << "Items in the room:\n";
        for (const auto& item : items) {
            std::cout << "- " << item->getName() << "\n";
        }
    }
}




