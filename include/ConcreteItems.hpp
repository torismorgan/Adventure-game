ConcreteItem.h
#ifndef CONCRETEITEMS_H
#define CONCRETEITEMS_H

#include "Item.h"

class Flashlight : public Item {
public:
    Flashlight();
    void use() override;
};