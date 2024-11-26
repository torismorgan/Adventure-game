#ifndef CONCRETEITEMS_HPP
#define CONCRETEITEMS_HPP

#include "Item.hpp"
#include <iostream>

// Flashlight
class Flashlight : public Item {
 public:
    Flashlight();
    void use() override;
};

// Key
class Key : public Item {
 public:
    Key();
    void use() override;
};

// Amulet
class Amulet : public Item {
 public:
    Amulet();
    void use() override;
};

#endif

