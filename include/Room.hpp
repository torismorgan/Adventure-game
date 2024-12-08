#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "Item.hpp"
#include "Door.hpp"

class Room {
private:
    std::string description;
    std::vector<std::shared_ptr<Item>> items;
    std::unordered_map<std::string, std::shared_ptr<Door>> exits;

public:
    Room(const std::string& desc);

    void describe() const;
    void addItem(std::shared_ptr<Item> item);
    void removeItem(std::shared_ptr<Item> item);
    std::vector<std::shared_ptr<Item>> getItems() const;
    void lockExit(const std::string& direction, std::shared_ptr<Item> key);
    std::shared_ptr<Door> getExit(const std::string& direction) const;
    std::string getDescription() const;
};

#endif // ROOM_HPP











