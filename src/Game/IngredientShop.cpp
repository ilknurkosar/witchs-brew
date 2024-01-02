#include "IngredientShop.hpp"

IngredientShop::IngredientShop() {
    // Initialize available ingredients here or in a separate function
    availableIngredients = {
        "100 Year Ginseng",
        "Spirit Grass",
        "Fire Essence",
        "Amethyst",
        "Water",
        "Speed Elixir"
    };
}

void IngredientShop::AddIngredient(const std::string& ingredientName) {
    availableIngredients.push_back(ingredientName);
    // Add logic for adding ingredient to the shop
}

void IngredientShop::RemoveIngredient(const std::string& ingredientName) {
    auto it = std::find(availableIngredients.begin(), availableIngredients.end(), ingredientName);
    if (it != availableIngredients.end()) {
        availableIngredients.erase(it);
        // Add logic for removing ingredient from the shop
    }
}

bool IngredientShop::HasIngredient(const std::string& ingredientName) const {
    return std::find(availableIngredients.begin(), availableIngredients.end(), ingredientName) != availableIngredients.end();
}

const std::vector<std::string>& IngredientShop::GetAvailableIngredients() const {
    return availableIngredients;
}
