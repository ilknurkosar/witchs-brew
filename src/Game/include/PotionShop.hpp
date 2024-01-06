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
    std::unique_ptr<InfiniteShop> ingredientSupplier = std::make_unique<InfiniteShop>();
    std::unique_ptr<InfiniteShop> upgradeSupplier= std::make_unique<InfiniteShop>();
    public:
    void buyUpgrade(Item upgrade);
    void buyIngredient(Item ingredient, float amount);
    void craftPotion();
    void uncraftPotion();

    inline const std::vector<Item>& getUpgrades() const {return upgrades;}
    inline Inventory& getIngredientss(){return potionIngredients;}
    inline InfiniteShop* getUpgradeShop() const {return upgradeSupplier.get();}
    inline InfiniteShop* getIngredientShop() const {return ingredientSupplier.get();}
    inline float getBalance(){return inventory.getItemAmount(Item::MONEY);}
    inline float getPrice(){return getDemand(Item::POTION).second;}
    inline void setPrice(float price){setDemand(Item::POTION, Item::MONEY, price);}

    PotionShop() = default;
    PotionShop(float balance);
    virtual ~PotionShop()= default;

};