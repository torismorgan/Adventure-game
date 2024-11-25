#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item {
protected:
    std::string name;
    std::string description;

public:
    virtual ~Item() = default;
    virtual void use() = 0;
    std::string getName() const;
    std::string getDescription() const;
};

#endif // ITEM_H