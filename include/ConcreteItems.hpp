#ifndef CONCRETEITEMS_HPP
#define CONCRETEITEMS_HPP

#include "Item.hpp"

class Flashlight : public Item {
public:
    Flashlight();
    void use() override;
};
class Key : public Item {
public:
    Key();
    void use() override;
};

class Amulet : public Item {
public:
    Amulet();
    void use() override;
};

class Map : public Item {
public:
    Map();
    void use() override;
};

class Book : public Item {
public:
    Book();
    void use() override;
};

#endif // CONCRETEITEMS_H