#pragma once
#include "EventQueue.hpp"
#include "Node.hpp"
#include "PotionShop.hpp"
#include "RunnableNode.hpp"

class DayTime: public Node, public RunnableNode {
    public:
    Event startNight;
    private:
    PotionShop* shop;
    public:
    void endDay();
    virtual void Init(void* data) override; // 2-stage constructor separate from constructor

    inline PotionShop* getShop() const { return shop;}

    explicit DayTime() = delete;
    explicit DayTime(PotionShop* shop);
    virtual ~DayTime() = default;
    virtual void process() override;
};