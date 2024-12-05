#include "Door.hpp"

Door::Door(bool locked, std::shared_ptr<Item> key) : isLocked(locked), requiredKey(key) {}

bool Door::unlock(const std::shared_ptr<Item>& key) {
    if (key && key == requiredKey) {
        isLocked = false; // Unlock the door
        return true;
    }
    return false; // Failed to unlock
}

bool Door::getIsLocked() const {
    return isLocked;
}