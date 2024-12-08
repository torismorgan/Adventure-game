#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Item.hpp"
#include "Door.hpp"

class Room {
private:
    std::string description;
    std::vector<std::shared_ptr<Item>> items;
    std::map<std::string, std::pair<std::shared_ptr<Room>, std::shared_ptr<Door>>> exits;

public:
    explicit Room(const std::string& desc);

    std::string getDescription() const;
    const std::vector<std::shared_ptr<Item>>& getItems() const;
    void addItem(std::shared_ptr<Item> item);
    void removeItem(std::shared_ptr<Item> item);
    void setExitWithDoor(const std::string& direction, std::shared_ptr<Room> room, std::shared_ptr<Door> door);
    std::shared_ptr<Room> getExit(const std::string& direction) const;
    bool isDoorLocked(const std::string& direction) const;
void enter() const; // Add declaration

    void describe() const; // Add this declaration
};

#endif // ROOM_HPP






