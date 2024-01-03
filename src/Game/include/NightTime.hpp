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
    virtual void process(double delta) override;
};