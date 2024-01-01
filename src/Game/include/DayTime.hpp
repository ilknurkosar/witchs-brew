#pragma once
#include "EventQueue.hpp"
#include "Node.hpp"
#include "RunnableNode.hpp"

class DayTime: public Node, public RunnableNode {
    private:
    Event endDay;
    public:
    DayTime();
    virtual void process(double delta) override;
};