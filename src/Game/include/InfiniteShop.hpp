#pragma once

#include "TradeAgent.hpp"
#include <string>
#include <vector>

class InfiniteShop : public TradeAgent {
private:

public:
    InfiniteShop()=default;

    void AddItem(Item upgrade, float price, const std::string name);
    void RemoveItem(Item upgrade);
};