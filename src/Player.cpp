#include "Player.hpp"
#include <iostream>
#include <algorithm>

Player::Player(std::shared_ptr<Room> startingRoom) 
    : currentRoom(startingRoom), hasTorchLit(false) {}

void Player::move(const std::string& direction) {
    auto room = currentRoom->getExit(direction);
    if (room) {
        currentRoom = room;
        currentRoom->describe();
    } else {
        std::cout << "There is no exit in that direction.\n";
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

const std::vector<std::shared_ptr<Item>>& Player::getInventory() const {
    return inventory;
}

std::shared_ptr<Room> Player::getCurrentRoom() const {
    return currentRoom;
}

void Player::lightTorch() {
    hasTorchLit = true;
    std::cout << "The torch is now lit.\n";
}

bool Player::isTorchLit() const {
    return hasTorchLit;
}

