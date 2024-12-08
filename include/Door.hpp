#ifndef DOOR_HPP
#define DOOR_HPP

#include "Item.hpp"
#include <memory>

class Door {
private:
    bool locked;
    std::shared_ptr<Key> requiredKey;
    std::shared_ptr<Room> connectedRoom;

public:
    Door(bool isLocked, std::shared_ptr<Room> room);
    void lock(std::shared_ptr<Key> key);
    void unlock(std::shared_ptr<Key> key);
    bool isLocked() const;
    std::shared_ptr<Room> getConnectedRoom() const;
};

#endif // DOOR_HPP



