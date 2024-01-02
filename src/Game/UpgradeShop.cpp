#include "UpgradeShop.hpp"

UpgradeShop::UpgradeShop(const std::string& agentName, float startingFunds) : TradeAgent(agentName, startingFunds) {
    // Initialize available upgrades or any other setup if needed
}

void UpgradeShop::AddUpgrade(const std::string& upgradeName) {
    availableUpgrades.push_back(upgradeName);
    // Add logic for adding upgrade to the shop
}

void UpgradeShop::RemoveUpgrade(const std::string& upgradeName) {
    // Find and remove the upgrade from the available upgrades list
    auto it = std::find(availableUpgrades.begin(), availableUpgrades.end(), upgradeName);
    if (it != availableUpgrades.end()) {
        availableUpgrades.erase(it);
        // Add logic for removing upgrade from the shop
    }
}

bool UpgradeShop::HasUpgrade(const std::string& upgradeName) const {
    return std::find(availableUpgrades.begin(), availableUpgrades.end(), upgradeName) != availableUpgrades.end();
}

const std::vector<std::string>& UpgradeShop::GetAvailableUpgrades() const {
    return availableUpgrades;
}
