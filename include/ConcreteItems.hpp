ConcreteItem.h
#ifndef CONCRETEITEMS_H
#define CONCRETEITEMS_H

#include "Item.h"

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