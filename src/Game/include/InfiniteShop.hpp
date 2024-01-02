#pragma once

#include "TradeAgent.hpp"
#include <string>
#include <vector>

class InfiniteShop : public TradeAgent {
private:

public:
    InfiniteShop()=default;

    void AddUpgrade(Item upgrade, float price, const std::string name);
    void RemoveUpgrade(Item upgrade);
};