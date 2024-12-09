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
    std::cout << item->getName() << " has been added to your inventory.\n"; // Debug message
}



void Player::dropItem(std::shared_ptr<Item> item) {
    inventory.erase(std::remove(inventory.begin(), inventory.end(), item), inventory.end());
}

std::shared_ptr<Item> Player::findItemInInventory(const std::string& itemName) const {
    std::string normalizedItemName = itemName;
    std::transform(normalizedItemName.begin(), normalizedItemName.end(), normalizedItemName.begin(), ::tolower);

    for (const auto& item : inventory) {
        std::string normalizedStoredName = item->getName();
        std::transform(normalizedStoredName.begin(), normalizedStoredName.end(), normalizedStoredName.begin(), ::tolower);

        if (normalizedStoredName == normalizedItemName) {
            return item; // Return the matching item
        }
    }
    return nullptr; // Return nullptr if no match is found
}

const std::vector<std::shared_ptr<Item>>& Player::getInventory() const {
    return inventory; // Simply return the inventory vector
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

