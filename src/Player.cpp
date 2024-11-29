#include "Player.hpp"

#include <algorithm>
#include <iostream>


Player::Player(std::shared_ptr<Room> startingRoom)
    : currentRoom(startingRoom) {}

bool Player::move(const std::string& direction) {
  if (!currentRoom) return false;

  auto nextRoom = currentRoom->getExit(direction);
  if (nextRoom) {
    currentRoom = nextRoom;
    currentRoom->enter();  // Ensure enter() is defined in Room
    return true;
  }
  return false;
}

bool Player::pickUp(std::shared_ptr<Item> item) {
  if (!item) return false;

  auto& roomItems =
      currentRoom->getItems();  // Ensure getItems() is defined in Room
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
}
bool Player::dropItem(const std::shared_ptr<Item>& item) {
    auto it = std::find(inventory.begin(), inventory.end(), item);
    if (it != inventory.end()) {
        inventory.erase(it); // Remove the item from the inventory
        return true;
    }
    return false; // Item not found in inventory
}

const std::vector<std::shared_ptr<Item>>& Player::getInventory() const {
    return inventory; // Return the player's inventory
}

std::shared_ptr<Room> Player::getCurrentRoom() const { return currentRoom; }
