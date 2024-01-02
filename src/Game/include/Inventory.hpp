#pragma once

#include "Item.hpp"
#include <map>
#include <vector>
#include <string>
#include <utility>

class Inventory {
private:
    std::map<Item, float> items;

public:
    Inventory();

    void addItem(Item item, float quantity);
    float takeItem(Item item, float quantity);
    void setItem(Item item, float quantity);
    inline std::map<Item, float>& getItems(){return items;} //HACK:
    void RemoveItem(Item item);
    bool hasItem(Item item) const;
    float getItemAmount(Item item);
    void clear();
};