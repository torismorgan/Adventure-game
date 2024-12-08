#ifndef ROOM_HPP
#define ROOM_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>
#include "Item.hpp"
#include "Door.hpp"

class Room {
private:
    std::string description;
    std::vector<std::shared_ptr<Item>> items;
    std::map<std::string, std::shared_ptr<Door>> exits;

public:
    Room(const std::string& desc);

    std::string getDescription() const;
    void addItem(std::shared_ptr<Item> item);
    void removeItem(std::shared_ptr<Item> item);
    const std::vector<std::shared_ptr<Item>>& getItems() const;

    void setExit(const std::string& direction, std::shared_ptr<Room> room);
    std::shared_ptr<Room> getExit(const std::string& direction) const;

    void lockExit(const std::string& direction, std::shared_ptr<Key> key);
    bool unlockExit(const std::string& direction, std::shared_ptr<Key> key);
};

#endif // ROOM_HPP







