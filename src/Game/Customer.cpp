#include "Customer.hpp"

Customer::Customer(const std::string& _name) : name(_name), money(0) {
    // Constructor logic if needed
}

const std::string& Customer::GetName() const {
    return name;
}

float Customer::GetMoney() const {
    return money;
}

void Customer::SetMoney(float amount) {
    money = amount;
    // Logic for setting customer's money
}

void Customer::Purchase(float amount) {
    if (money >= amount) {
        money -= amount;
        // Logic for customer's purchase
    } else {
        // Handle insufficient funds scenario
    }
}
