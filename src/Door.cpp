#include "Door.hpp"

Door::Door(bool isLocked, std::shared_ptr<Room> room)
    : isLocked(isLocked), connectedRoom(room) {}

void Door::lock(std::shared_ptr<Flashlight> key) {
    isLocked = true;
    requiredKey = key;
}

void Door::unlock(std::shared_ptr<Flashlight> key) {
    if (requiredKey && key->getName() == requiredKey->getName()) {
        isLocked = false;
        std::cout << "The door has been unlocked.\n";
    } else {
        std::cout << "The key doesn't fit.\n";
    }
}

bool Door::isLocked() const {
    return isLocked;
}

std::shared_ptr<Room> Door::getConnectedRoom() const {
    return connectedRoom;
}
