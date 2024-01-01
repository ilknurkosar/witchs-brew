#pragma once

#include <string>

class TradeAgent {
protected:
    std::string name;
    float funds;
    // Other member variables if needed

public:
    TradeAgent(const std::string& agentName, float startingFunds);

    const std::string& GetName() const;
    float GetFunds() const;
    void AddFunds(float amount);
    void DeductFunds(float amount);
};

