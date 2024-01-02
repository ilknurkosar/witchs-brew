#include "PotionShop.hpp"
#include "Inventory.hpp"
#include <algorithm>
#include <cmath>
#include <limits>

PotionShop::PotionShop(float balance)
: PotionShop()
{
    inventory.addItem(Item::MONEY, balance);
}

void PotionShop::buyUpgrade(Item upgrade){
    if(inventory.getItemAmount(upgrade) == 1.0)
        return; // already bought
    float balance = inventory.getItemAmount(Item::MONEY);
    float res = buy(upgradeSupplier.get(), upgrade, 1.0);
    if(res != 1.0){
        inventory.setItem(Item::MONEY, balance);
        return; // not enough money
    }
    upgrades.push_back(upgrade);
}

void PotionShop::buyIngredient(Item ingredient, float amount){
    buy(ingredientSupplier.get(), ingredient, amount);
}

void PotionShop::craftPotion(){
    float amount = std::numeric_limits<float>::max();
    for(auto ingredient: potionIngredients.getItems()){
        float avail = inventory.getItemAmount(ingredient.first);
        amount = std::min(amount,avail/ingredient.second);
    }
    for(auto ingredient: potionIngredients.getItems())
        inventory.takeItem(ingredient.first, amount*ingredient.second);
    inventory.addItem(Item::POTION, amount);
}
void PotionShop::uncraftPotion(){
    float amount = inventory.getItemAmount(Item::POTION);
    for(auto ingredient: potionIngredients.getItems())
        inventory.addItem(ingredient.first, ingredient.second*amount);
}