#ifndef DOOR_HPP
#define DOOR_HPP

#include <memory>
#include <string>
#include "Room.hpp"
#include "ConcreteItems.hpp" // Include this for the Key class in ConcreteItems

class Door {
private:
    bool isLocked;
    std::shared_ptr<Flashlight> requiredKey; // Use the Key from ConcreteItems
    std::shared_ptr<Room> connectedRoom;

public:
    Door(bool isLocked, std::shared_ptr<Room> room);

    void lock(std::shared_ptr<Flashlight> key);
    void unlock(std::shared_ptr<Flashlight> key);

    bool isLocked() const;
    std::shared_ptr<Room> getConnectedRoom() const;
};

#endif // DOOR_HPP




