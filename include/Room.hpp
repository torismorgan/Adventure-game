#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Item.hpp"
#include "Puzzle.hpp"

class Room {
protected:
    std::string description;
    std::vector<std::shared_ptr<Item>> items;
    std::map<std::string, std::shared_ptr<Room>> exits;
    std::shared_ptr<Puzzle> puzzle;

public:
    Room(const std::string& desc);
    virtual ~Room() = default;

    virtual void enter();
    std::string getDescription() const;
    void addItem(std::shared_ptr<Item> item);
    void removeItem(std::shared_ptr<Item> item);
    std::shared_ptr<Room> getExit(const std::string& direction) const;
    void setExit(const std::string& direction, std::shared_ptr<Room> room);

    // Additional utility methods
    const std::vector<std::shared_ptr<Item>>& getItems() const;
    void setPuzzle(std::shared_ptr<Puzzle> newPuzzle);
    std::shared_ptr<Puzzle> getPuzzle() const;
    bool hasExit(const std::string& direction) const;
};

#endif // ROOM_H
