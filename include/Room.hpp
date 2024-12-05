#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include "Item.hpp"
#include "Door.hpp"

class Room {
private:
    std::string description;
    std::vector<std::shared_ptr<Item>> items;
    std::map<std::string, std::pair<std::shared_ptr<Room>, std::shared_ptr<Door>>> exits;

public:
    explicit Room(const std::string& desc) : description(desc) {}

    std::string getDescription() const { return description; }
    const std::vector<std::shared_ptr<Item>>& getItems() const { return items; }
    void addItem(std::shared_ptr<Item> item) { if (item) items.push_back(item); }
    void removeItem(std::shared_ptr<Item> item) {
        auto it = std::find(items.begin(), items.end(), item);
        if (it != items.end()) items.erase(it);
    }

    void setExitWithDoor(const std::string& direction, std::shared_ptr<Room> room, std::shared_ptr<Door> door) {
        if (room) exits[direction] = {room, door};
    }

    std::shared_ptr<Room> getExit(const std::string& direction) const {
        auto it = exits.find(direction);
        return it != exits.end() ? it->second.first : nullptr;
    }

    std::shared_ptr<Door> getDoor(const std::string& direction) const {
        auto it = exits.find(direction);
        return it != exits.end() ? it->second.second : nullptr;
    }

    bool isDoorLocked(const std::string& direction) const {
        auto door = getDoor(direction);
        return door ? door->getIsLocked() : false;
    }

    void describe() const {
        std::cout << "You are in: " << description << "\nItems in the room: ";
        for (const auto& item : items) {
            std::cout << item->getName() << " ";
        }
        std::cout << "\n";
    }
};

#endif // ROOM_HPP





