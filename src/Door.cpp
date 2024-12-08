#include "Door.hpp"

Door::Door(bool isLocked, std::shared_ptr<Room> room)
    : locked(isLocked), connectedRoom(room) {}

void Door::lock(std::shared_ptr<Item> key) {
    requiredKey = key;
    locked = true;
}

void Door::unlock(std::shared_ptr<Item> key) {
    if (requiredKey && key->getName() == requiredKey->getName()) {
        locked = false;
        requiredKey = nullptr;
        std::cout << "The door has been unlocked.\n";
    } else {
        std::cout << "The key does not fit.\n";
    }
}

bool Door::isLocked() const {
    return locked;
}

std::shared_ptr<Room> Door::getConnectedRoom() const {
    return connectedRoom;
}

