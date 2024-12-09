#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item {
protected:
    std::string name;
    std::string description;

public:
    virtual ~Item() = default;

    // Getters
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
std::shared_ptr<Item> findItem(const std::string& itemName) const;


    // Virtual use function to be overridden by specific items
    virtual void use() = 0;
};

#endif // ITEM_HPP
