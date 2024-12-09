#ifndef ROOM_HPP
#define ROOM_HPP

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "Item.hpp"
#include "NPC.hpp"
#include "Puzzle.hpp"

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
    std::shared_ptr<Item> findItem(const std::string& itemName) const;

    void setExit(const std::string& direction, std::shared_ptr<Room> room);
    std::shared_ptr<Room> getExit(const std::string& direction) const;

    void setNPC(std::shared_ptr<NPC> npc) { this->npc = npc; }
    std::shared_ptr<NPC> getNPC() const { return npc; }

    void setPuzzle(std::shared_ptr<Puzzle> puzzle) { this->puzzle = puzzle; }
    std::shared_ptr<Puzzle> getPuzzle() const { return puzzle; }
    bool isPuzzleSolved() const { return puzzle ? puzzle->getIsSolved() : true; }
    std::string getDescription() const { return description; }
};

#endif // ROOM_HPP



