#include "PotionShop.h"
#include "Node.h"
#include "Node2D.h"
#include "Customer.h"

PotionShop::PotionShop() : isGameRunning(false)
{
    Node2D *mainMenu = new Node2D();
    nodes.push_back(mainMenu);
    PopulateInitialInventory();
}

PotionShop::~PotionShop()
{
    for (auto &node : nodes)
    {
        delete node;
    }
    nodes.clear();
    for (auto &customer : customers)
    {
        delete customer;
    }
    customers.clear();
    shopInventory.ClearInventory();
}

void PotionShop::InitGame()
{
    // Initialization code as before
}

void PotionShop::AddCustomer(Customer *customer)
{
    customers.push_back(customer);
}

void PotionShop::RemoveCustomer(Customer *customer)
{
    // Find and remove the customer from the list
    auto it = std::find(customers.begin(), customers.end(), customer);
    if (it != customers.end())
    {
        customers.erase(it);
        delete customer; // Optionally delete the customer object
    }
}

void PotionShop::Update()
{
    // Update logic as before
}

void PotionShop::AddItemToInventory(const std::string &itemName, int quantity)
{
    shopInventory.AddItem(itemName, quantity);
}

void PotionShop::RemoveItemFromInventory(const std::string &itemName, int quantity)
{
    shopInventory.RemoveItem(itemName, quantity);
}

bool PotionShop::HasItemInInventory(const std::string &itemName) const
{
    return shopInventory.HasItem(itemName);
}

void PotionShop::AdjustShopFunds(float amount)
{
    // Adjust shop funds logic as before
}

void PotionShop::Render()
{
    // Render logic as before
}

void PotionShop::Run()
{
    // Run logic as before
}
