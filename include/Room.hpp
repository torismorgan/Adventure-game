#ifndef ROOM_HPP
#define ROOM_HPP

#include "Item.hpp"
#include "Door.hpp"
#include <string>
#include <memory>
#include <map>
#include <vector>

class Room {
private:
    std::string description;
    std::vector<std::shared_ptr<Item>> items;
    std::map<std::string, std::shared_ptr<Door>> exits;

public:
    Room(const std::string& desc);

    void setExit(const std::string& direction, std::shared_ptr<Room> connectedRoom);
    void lockExit(const std::string& direction, std::shared_ptr<Key> key);

    std::string getDescription() const;
    std::vector<std::shared_ptr<Item>>& getItems();
    void addItem(std::shared_ptr<Item> item);
    void removeItem(std::shared_ptr<Item> item);
    std::shared_ptr<Door> getExit(const std::string& direction);
    void describe() const;
};

#endif // ROOM_HPP








