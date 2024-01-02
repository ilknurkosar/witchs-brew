#include "TradeAgent.hpp"

TradeAgent::TradeAgent(const std::string& agentName, float startingFunds) : name(agentName), funds(startingFunds) {
    // Constructor logic if needed
}

const std::string& TradeAgent::GetName() const {
    return name;
}

float TradeAgent::GetFunds() const {
    return funds;
}

void TradeAgent::AddFunds(float amount) {
    funds += amount;
    // Add logic for fund addition
}

void TradeAgent::DeductFunds(float amount) {
    if (amount <= funds) {
        funds -= amount;
        // Add logic for fund deduction
    } else {
        // Handle insufficient funds scenario
    }
}
