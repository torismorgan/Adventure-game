#ifndef DOOR_HPP
#define DOOR_HPP

#include <memory>
#include <string>
#include "Item.hpp"

// Forward declaration of Room
class Room;

class Door {
private:
    bool locked;
    std::shared_ptr<Item> requiredKey;
    std::shared_ptr<Room> connectedRoom;

public:
    Door(bool isLocked, std::shared_ptr<Room> room);

    void lock(std::shared_ptr<Item> key);
    void unlock(std::shared_ptr<Item> key);

    bool isLocked() const;
    std::shared_ptr<Room> getConnectedRoom() const;
};

#endif // DOOR_HPP






