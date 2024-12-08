#include "Door.hpp"

Door::Door(bool isLocked, std::shared_ptr<Room> room) 
    : locked(isLocked), connectedRoom(room) {}

void Door::lock(std::shared_ptr<Key> key) {
    locked = true;
    requiredKey = key;
}

void Door::unlock(std::shared_ptr<Key> key) {
    if (key == requiredKey) {
        locked = false;
    }
}

bool Door::isLocked() const {
    return locked;
}

std::shared_ptr<Room> Door::getConnectedRoom() const {
    return connectedRoom;
}
