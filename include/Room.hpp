#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Item.hpp"

class Room {
 private:
    std::string description;
    std::vector<std::shared_ptr<Item>> items;
    std::map<std::string, std::shared_ptr<Room>> exits;

 public:
    Room(const std::string& desc);

    std::string getDescription() const;
    void enter();  // Add this declaration
    void describe() const;

    void addItem(std::shared_ptr<Item> item);
    void removeItem(std::shared_ptr<Item> item);

    void setExit(const std::string& direction, std::shared_ptr<Room> room);
    std::shared_ptr<Room> getExit(const std::string& direction) const;

    const std::vector<std::shared_ptr<Item>>& getItems() const;
};

#endif


