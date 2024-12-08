#include "Player.hpp"
#include "Room.hpp"
#include <algorithm>
#include <iostream>

Player::Player(std::shared_ptr<Room> startingRoom)
    : currentRoom(startingRoom) {}

void Player::move(const std::string& direction) {
    auto door = currentRoom->getExit(direction);
    if (door && !door->isLocked()) {
        currentRoom = door->getConnectedRoom();
        currentRoom->describe();
    } else {
        std::cout << "The door is locked or does not exist.\n";
    }
}

void Player::pickUp(std::shared_ptr<Item> item) {
    inventory.push_back(item);
}

void Player::dropItem(std::shared_ptr<Item> item) {
    inventory.erase(std::remove(inventory.begin(), inventory.end(), item), inventory.end());
}

std::shared_ptr<Item> Player::findItemInInventory(const std::string& itemName) const {
    for (const auto& item : inventory) {
        if (item->getName() == itemName) {
            return item;
        }
    }
    return nullptr;
}

std::shared_ptr<Room> Player::getCurrentRoom() const {
    return currentRoom;
}
