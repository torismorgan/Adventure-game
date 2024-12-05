#ifndef DOOR_HPP
#define DOOR_HPP

#include "Item.hpp"
#include <memory>

class Door {
private:
    bool isLocked;
    std::shared_ptr<Item> requiredKey;

public:
    Door(bool locked, std::shared_ptr<Item> key) : isLocked(locked), requiredKey(key) {}
   
    bool unlock(const std::shared_ptr<Item>& key) {
        if (key && key == requiredKey) {
            isLocked = false;
            return true;
        }
        return false;
    }

    bool getIsLocked() const { return isLocked; }
};

#endif // DOOR_HPP


