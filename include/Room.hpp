#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "Item.hpp"
#include "NPC.hpp"
#include "Puzzle.hpp"

class Door;

class Room {
private:
    std::string description;
    std::vector<std::shared_ptr<Item>> items;
    std::unordered_map<std::string, std::shared_ptr<Room>> exits;
    std::shared_ptr<NPC> npc;
    std::shared_ptr<Puzzle> puzzle;

public:
    Room(const std::string& desc);

    void describe() const;
    void addItem(std::shared_ptr<Item> item);
    void removeItem(std::shared_ptr<Item> item);
    const std::vector<std::shared_ptr<Item>>& getItems() const;

    void setExit(const std::string& direction, std::shared_ptr<Room> room);
    std::shared_ptr<Room> getExit(const std::string& direction) const;

    void setNPC(std::shared_ptr<NPC> npc);
    std::shared_ptr<NPC> getNPC() const;

    void setPuzzle(std::shared_ptr<Puzzle> puzzle);
    std::shared_ptr<Puzzle> getPuzzle() const;
    std::string getDescription() const;

};

#endif // ROOM_HPP












