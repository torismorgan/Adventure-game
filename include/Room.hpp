#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "Item.hpp"
#include "NPC.hpp"
#include "Puzzle.hpp"

class Room {
private:
    std::string description;
    std::vector<std::shared_ptr<Item>> items;
    std::shared_ptr<NPC> npc;
    std::shared_ptr<Puzzle> puzzle;
    std::unordered_map<std::string, std::shared_ptr<Room>> exits;

public:
    Room(const std::string& desc);

    // Room description
    void describe() const;

    // Item management
    void addItem(std::shared_ptr<Item> item);
    void removeItem(std::shared_ptr<Item> item);
    std::shared_ptr<Item> findItem(const std::string& itemName) const;

    // NPC management
    void setNPC(std::shared_ptr<NPC> npc);
    std::shared_ptr<NPC> getNPC() const;

    // Puzzle management
    void setPuzzle(std::shared_ptr<Puzzle> puzzle);
    std::shared_ptr<Puzzle> getPuzzle() const;
    bool isPuzzleSolved() const;

    // Room exits
    void setExit(const std::string& direction, std::shared_ptr<Room> room);
    std::shared_ptr<Room> getExit(const std::string& direction) const;

    // Room description getter
    std::string getDescription() const;
};
