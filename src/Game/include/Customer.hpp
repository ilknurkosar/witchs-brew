#pragma once

#include <string>

class Customer {
private:
    std::string name;
    float money;
    // Other member variables if needed

public:
    Customer(const std::string& _name);

    const std::string& GetName() const;
    float GetMoney() const;
    void SetMoney(float amount);
    void Purchase(float amount);
    // Other methods for customer interactions
};
