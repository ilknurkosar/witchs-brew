#pragma once
#include "EventQueue.hpp"
#include "Node.hpp"
#include "RunnableNode.hpp"

class NightTime: public Node, public RunnableNode {
    private:
    Event endNight;
    public:
    NightTime();
    virtual void process(double delta) override;
};