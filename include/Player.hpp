#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>
#include <utility>
#include <string>
#include "Room.hpp"
#include "Item.hpp"

class Player {
 private:
    std::shared_ptr<Room> currentRoom;
    std::vector<std::shared_ptr<Item>> inventory;

 public:
    Player(std::shared_ptr<Room> startingRoom);

    bool move(const std::string& direction);
    bool pickUp(std::shared_ptr<Item> item);
    bool useItem(std::shared_ptr<Item> item);
    const std::vector<std::shared_ptr<Item>>& getInventory() const;
    std::shared_ptr<Room> getCurrentRoom() const;

    // Additional utility methods
    bool hasItem(const std::shared_ptr<Item>& item) const;
   // bool dropItem(std::shared_ptr<Item> item);
    bool dropItem(const std::shared_ptr<Item>& item); // Declare dropItem method
     const std::vector<std::shared_ptr<Item>>& getInventory() const;
    // Other methods like move(), pickUp(), dropItem(), etc.
};


#endif // PLAYER_H
