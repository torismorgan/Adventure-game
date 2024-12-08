#include "Door.hpp"

Door::Door(bool locked, std::shared_ptr<Item> key) : isLocked(locked), requiredKey(key) {}

bool Door::unlock(const std::shared_ptr<Item>& key) {
    if (key && key == requiredKey) {
        isLocked = false;
        return true;
    }
    return false;
}

bool Door::getIsLocked() const {
    return isLocked;
}
