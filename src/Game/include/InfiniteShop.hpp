#pragma once

#include "TradeAgent.hpp"
#include <string>
#include <vector>

class InfiniteShop : public TradeAgent {
private:

public:
    InfiniteShop()=default;

    void AddItem(Item upgrade, float price, const std::string name, std::string desc);
    void RemoveItem(Item upgrade);
};