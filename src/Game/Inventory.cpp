#include "Inventory.hpp"
#include <algorithm>

Inventory::Inventory()
: items()
{

}

void Inventory::addItem(Item item, float quantity){
    float temp = hasItem(item) ? items[item] : 0.0f;
    items[item] = temp + quantity;
}
float Inventory::takeItem(Item item, float quantity){
    float temp = items[item];
    items[item] = std::max(temp-quantity, 0.0f);
    return temp > quantity ? quantity : temp;
}


void Inventory::setItem(Item item, float quantity) {
    items[item] = quantity; // override if it exists previously
}

void Inventory::RemoveItem(Item item) {
    items.erase(item);
}

bool Inventory::hasItem(Item item) const {
    return items.count(item) > 0;
}

float Inventory::getItemAmount(Item item){
    return hasItem(item) ? items[item] : 0.0f;
}

void Inventory::clear() {
    items.clear();
}
