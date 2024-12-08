#ifndef DOOR_HPP
#define DOOR_HPP

#include "Item.hpp"
#include <memory>

class Door {
private:
    bool isLocked;
    std::shared_ptr<Item> requiredKey;

public:
    Door(bool locked, std::shared_ptr<Item> key);
    bool unlock(const std::shared_ptr<Item>& key);
    bool getIsLocked() const;
};

#endif // DOOR_HPP


