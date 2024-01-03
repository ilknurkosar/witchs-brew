#pragma once
#include "EventQueue.hpp"
#include "Node.hpp"
#include "PotionShop.hpp"
#include "RunnableNode.hpp"

class DayTime: public Node, public RunnableNode {
    private:
    PotionShop* shop;
    Event endDay;
    public:
    DayTime();
    virtual ~DayTime() = default;
    // virtual void Init(void** data) override; // 2-stage constructor separate from constructor
    virtual void process(double delta) override;
};