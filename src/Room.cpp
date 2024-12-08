#include "Room.hpp"
#include "Door.hpp"
#include <iostream>

Room::Room(const std::string& desc) : description(desc) {}

void Room::describe() const {
    std::cout << description << "\nItems in the room:\n";
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

std::vector<std::shared_ptr<Item>> Room::getItems() const {
    return items;
}

void Room::setExit(const std::string& direction, std::shared_ptr<Room> room) {
    exits[direction] = std::make_shared<Door>(false, room);
}

std::shared_ptr<Door> Room::getExit(const std::string& direction) const {
    auto it = exits.find(direction);
    if (it != exits.end()) {
        return it->second;
    }
    return nullptr;
}



