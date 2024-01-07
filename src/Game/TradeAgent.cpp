#include "TradeAgent.hpp"
#include "Item.hpp"
#include <utility>

void TradeAgent::appendItem(Item item, float quantity, std::string label, std::string description){
    inventory.addItem(item, quantity);
    labels[item] = label;
    descriptions[item] = description;
}

float TradeAgent::sell(TradeAgent* buyer,Item item, float quantity){
    auto demand = getDemand(item);
    if(demand.first.id == -1 || !buyer->inventory.hasItem(demand.first))
        return 0.0f;
    float out = buyer->inventory.takeItem(demand.first, quantity*demand.second);
    float given =this->inventory.takeItem(item, out/demand.second);
    buyer->inventory.addItem(item, given);
    return out;
}

void TradeAgent::setDemand(Item give, Item receive, float price){
    demands[give] = std::pair<Item, float>{receive,price};
}

const std::vector<Item> TradeAgent::GetAvailableItems() const{
    std::vector<Item> out{};
    for (auto& name : labels) {
        out.push_back(name.first);
    }
    return out;
}