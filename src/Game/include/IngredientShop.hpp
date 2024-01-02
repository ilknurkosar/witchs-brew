#pragma once

#include <string>
#include <vector>

class IngredientShop {
private:
    std::vector<std::string> availableIngredients;
    // Other member variables or methods if needed

public:
    IngredientShop();

    void AddIngredient(const std::string& ingredientName);
    void RemoveIngredient(const std::string& ingredientName);
    bool HasIngredient(const std::string& ingredientName) const;
    const std::vector<std::string>& GetAvailableIngredients() const;
};
