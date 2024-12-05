#include "Room.hpp"
#include <algorithm>

// Constructor
Room::Room(const std::string& desc) : description(desc) {}

// Get the description of the room
std::string Room::getDescription() const {
    return description;
}

// Get the items in the room
const std::vector<std::shared_ptr<Item>>& Room::getItems() const {
    return items;
}

// Add an item to the room
void Room::addItem(std::shared_ptr<Item> item) {
    if (item) {
        items.push_back(item);
    }
}

// Remove an item from the room
void Room::removeItem(std::shared_ptr<Item> item) {
    auto it = std::find(items.begin(), items.end(), item);
    if (it != items.end()) {
        items.erase(it);
    }
}

// Set an exit with a door
void Room::setExitWithDoor(const std::string& direction, std::shared_ptr<Room> room, std::shared_ptr<Door> door) {
    if (room) {
        exits[direction] = {room, door};
    }
}

// Get the room in the given direction
std::shared_ptr<Room> Room::getExit(const std::string& direction) const {
    auto it = exits.find(direction);
    if (it != exits.end()) {
        return it->second.first; // Return the connected room
    }
    return nullptr;
}

// Get the door in the given direction
std::shared_ptr<Door> Room::getDoor(const std::string& direction) const {
    auto it = exits.find(direction);
    if (it != exits.end()) {
        return it->second.second; // Return the door
    }
    return nullptr;
}

// Check if the door in the given direction is locked
bool Room::isDoorLocked(const std::string& direction) const {
    auto door = getDoor(direction);
    return door ? door->getIsLocked() : false;
}

// Enter the room
void Room::enter() {
    // Base implementation - can be overridden if needed
    std::cout << "You enter the room. " << description << "\n";
}



