#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "Item.hpp"
#include "Door.hpp"
#include "ConcreteItems.hpp" // For using the Key or other items in ConcreteItems

class Room {
private:
    std::string description;
    std::unordered_map<std::string, std::shared_ptr<Door>> exits;
    std::vector<std::shared_ptr<Item>> items;

public:
    Room(const std::string& description);

    void describe() const;
    void addItem(std::shared_ptr<Item> item);
    void removeItem(std::shared_ptr<Item> item);
    std::vector<std::shared_ptr<Item>>& getItems();

    void setExit(const std::string& direction, std::shared_ptr<Room> room);
    void lockExit(const std::string& direction, std::shared_ptr<Flashlight> key);
    std::shared_ptr<Door> getExit(const std::string& direction) const;
};

#endif // ROOM_HPP








