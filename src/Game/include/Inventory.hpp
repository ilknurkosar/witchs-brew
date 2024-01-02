#pragma once

#include <vector>
#include <string>
#include <utility>

class Inventory {
private:
    std::vector<std::pair<std::string, int>> items;

public:
    Inventory();

    void AddItem(const std::string& itemName, int quantity);
    void RemoveItem(const std::string& itemName, int quantity);
    bool HasItem(const std::string& itemName) const;
    int GetItemCount(const std::string& itemName) const;
    void ClearInventory();
};