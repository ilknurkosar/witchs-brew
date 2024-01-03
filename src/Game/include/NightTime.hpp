#pragma once
#include "DayTime.hpp"
#include "EventQueue.hpp"
#include "Node.hpp"
#include "PotionShop.hpp"
#include "RunnableNode.hpp"

class NightTime: public Node, public RunnableNode {
    private:
    PotionShop* shop;
    Event endNight;
    public:
    NightTime();
    virtual ~NightTime()=default;
    // virtual void Init(void** data) override; // 2-stage constructor separate from constructor
    virtual void process(double delta) override;
};