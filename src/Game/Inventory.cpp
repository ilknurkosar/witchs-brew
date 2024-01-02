#include "Inventory.hpp"

Inventory::Inventory() {
    // Constructor initialization if needed
}

void Inventory::AddItem(const std::string& itemName, int quantity) {
    for (auto& item : items) {
        if (item.first == itemName) {
            item.second += quantity;
            return;
        }
    }
    items.emplace_back(itemName, quantity);
}

void Inventory::RemoveItem(const std::string& itemName, int quantity) {
    for (auto& item : items) {
        if (item.first == itemName) {
            item.second -= quantity;
            if (item.second <= 0) {
                items.erase(std::remove(items.begin(), items.end(), item), items.end());
            }
            return;
        }
    }
}

bool Inventory::HasItem(const std::string& itemName) const {
    for (const auto& item : items) {
        if (item.first == itemName) {
            return true;
        }
    }
    return false;
}

int Inventory::GetItemCount(const std::string& itemName) const {
    for (const auto& item : items) {
        if (item.first == itemName) {
            return item.second;
        }
    }
    return 0;
}

void Inventory::ClearInventory() {
    items.clear();
}
