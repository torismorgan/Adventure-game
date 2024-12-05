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
    std::string description; // Description of the room
    std::vector<std::shared_ptr<Item>> items; // Items in the room
    std::map<std::string, std::pair<std::shared_ptr<Room>, std::shared_ptr<Door>>> exits; // Exits with optional doors

public:
    // Constructor
    explicit Room(const std::string& desc);

    // Getters
    std::string getDescription() const;
    const std::vector<std::shared_ptr<Item>>& getItems() const;

    // Room interaction
    void addItem(std::shared_ptr<Item> item); // Add an item to the room
    void removeItem(std::shared_ptr<Item> item); // Remove an item from the room
    void setExitWithDoor(const std::string& direction, std::shared_ptr<Room> room, std::shared_ptr<Door> door); // Add an exit with a door
    std::shared_ptr<Room> getExit(const std::string& direction) const; // Get the room in the given direction
    std::shared_ptr<Door> getDoor(const std::string& direction) const; // Get the door in the given direction
    bool isDoorLocked(const std::string& direction) const; // Check if a door is locked

    virtual void enter(); // Virtual function for entering the room
};

#endif // ROOM_HPP


