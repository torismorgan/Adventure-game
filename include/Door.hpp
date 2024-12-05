#ifndef DOOR_HPP
#define DOOR_HPP

#include <memory>
#include <string>
#include "Item.hpp"

class Door {
private:
    bool isLocked;
    std::shared_ptr<Item> requiredKey; // The key required to unlock the door

public:
    Door(bool locked, std::shared_ptr<Item> key);
    bool unlock(const std::shared_ptr<Item>& key); // Attempt to unlock the door
    bool getIsLocked() const; // Check if the door is locked
};

#endif // DOOR_HPP