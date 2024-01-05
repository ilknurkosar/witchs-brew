#pragma once
#include "EventQueue.hpp"
#include "Node.hpp"
#include "PotionShop.hpp"
#include "RunnableNode.hpp"

class NightTime: public Node, public RunnableNode {
    public:
    Event startDay;
    private:
    PotionShop* shop;
    public:
    void endNight();
    virtual void Init(void* data)override;

    inline PotionShop* getShop() const { return shop;}

    explicit NightTime() = delete;
    explicit NightTime(PotionShop* shop);
    virtual ~NightTime()=default;
    virtual void process() override;
};