#pragma once

#include "Inventory.hpp"
#include "Item.hpp"
#include <map>
#include <string>
#include <utility>
class TradeAgent {
protected:
    Inventory inventory;
    std::map<Item, std::string> labels;
    std::map<Item, std::pair<Item, float>> demands;
public:
    float sell(TradeAgent* buyer,Item item, float quantity);
    inline float buy(TradeAgent* seller,Item item, float quantity){return seller->sell(this, item, quantity);}

    void appendItem(Item item, float quantity, std::string label);
    void setDemand(Item give, Item receive, float price);
    const std::vector<Item> GetAvailableItems() const;

    inline const bool hasDemand(const Item item){return demands.count(item) > 0;}
    inline const std::string& getLabel(const Item item){return labels[item];}
    inline const float getStock(const Item item){return inventory.getItemAmount(item);}
    inline std::pair<Item, float> getDemand(Item item){return hasDemand(item) ? demands[item] : std::pair<Item,float>{Item{-1},0.0};}

    TradeAgent() = default;
    virtual ~TradeAgent() = default;
};

