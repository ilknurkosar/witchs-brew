#pragma once

#include "TradeAgent.hpp"
#include <string>
#include <vector>

class UpgradeShop : public TradeAgent {
private:
    std::vector<std::string> availableUpgrades;
    // Other member variables or methods if needed

public:
    UpgradeShop(const std::string& agentName, float startingFunds);

    void AddUpgrade(const std::string& upgradeName);
    void RemoveUpgrade(const std::string& upgradeName);
    bool HasUpgrade(const std::string& upgradeName) const;
    const std::vector<std::string>& GetAvailableUpgrades() const;
};