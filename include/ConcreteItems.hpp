#ifndef CONCRETEITEMS_HPP
#define CONCRETEITEMS_HPP

#include "Item.hpp"
#include <string>
#include <iostream>

// Flashlight Class
class Flashlight : public Item {
public:
    Flashlight();
    void use() override;
};

// Key Class
class Key : public Item {
public:
    Key(const std::string& keyName);
    void use() override;
};

// Amulet Class
class Amulet : public Item {
public:
    Amulet();
    void use() override;
};

#endif // CONCRETEITEMS_HPP






