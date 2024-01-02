#include "InfiniteShop.hpp"
#include "Inventory.hpp"
#include <limits>

void InfiniteShop::AddUpgrade(Item upgrade, float price, const std::string name){
    appendItem(upgrade, std::numeric_limits<float>::infinity(), name);
    setDemand(upgrade, Item::MONEY, price);
}

//intentionally didn't put any safeguard
void InfiniteShop::RemoveUpgrade(Item upgrade){
    inventory.RemoveItem(upgrade);
    demands.erase(upgrade);
    labels.erase(upgrade);
}