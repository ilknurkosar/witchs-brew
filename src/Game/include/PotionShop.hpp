#pragma once

#include "InfiniteShop.hpp"
#include "Inventory.hpp"
#include "Item.hpp"
#include "Node.hpp"
#include "TradeAgent.hpp"
#include <memory>
#include <vector>

class PotionShop : public TradeAgent, public Node{
    private:
    std::vector<Item> upgrades;
    Inventory potionIngredients;
    std::unique_ptr<InfiniteShop> ingredientSupplier;
    std::unique_ptr<InfiniteShop> upgradeSupplier;
    public:
    void buyUpgrade(Item upgrade);
    void buyIngredient(Item ingredient, float amount);
    void craftPotion();
    void uncraftPotion();

    inline std::vector<Item>& getUpgrades(){return upgrades;}
    inline Inventory& getIngredientss(){return potionIngredients;}
    inline InfiniteShop& getUpgradeShop(){return *upgradeSupplier;}
    inline void setUpgradeShop(InfiniteShop* shop){upgradeSupplier.reset(shop);}
    inline InfiniteShop& getIngredientShop(){return *ingredientSupplier;}
    inline void setIngredientShop(InfiniteShop* shop){ingredientSupplier.reset(shop);}

    PotionShop() = default;
    PotionShop(float balance);
    virtual ~PotionShop()= default;

};