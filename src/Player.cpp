#include "Player.hpp"
#include <iostream>
#include <algorithm>

Player::Player(std::shared_ptr<Room> startingRoom) : currentRoom(startingRoom) {}

bool Player::move(const std::string& direction) {
    if (!currentRoom) return false;

    auto nextRoom = currentRoom->getExit(direction);
    if (nextRoom) {
        currentRoom = nextRoom;
        currentRoom->enter();
        return true;
    }
    return false;
}

bool Player::pickUp(std::shared_ptr<Item> item) {
    if (!item) return false;

    auto& roomItems = currentRoom->getItems();
    auto it = std::find(roomItems.begin(), roomItems.end(), item);

    if (it != roomItems.end()) {
        inventory.push_back(item);
        currentRoom->removeItem(item);
        return true;
    }
    return false;
}

bool Player::useItem(std::shared_ptr<Item> item) {
    if (!item) return false;

    auto it = std::find(inventory.begin(), inventory.end(), item);
    if (it != inventory.end()) {
        (*it)->use();
        return true;
    }
    return false;
}*/

std::shared_ptr<Room> Player::getCurrentRoom() const {
    return currentRoom;
}


