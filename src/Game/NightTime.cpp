#include "NightTime.hpp"
#include "Event.hpp"
#include "EventQueue.hpp"
#include "Global.hpp"
#include "PotionShop.hpp"
#include <iostream>
NightTime::NightTime(PotionShop* shop)
: shop(shop), startDay(501)
{

}

void NightTime::process(){
    return;
}
void NightTime::endNight(){
    EventQueue::fireEvent(startDay, 0);
    disable();
    makeInvisible();
}

void NightTime::Init(void* data){
    Event startNight = *((Event*)data);
    EventHandler handle = [this](void* x)-> bool{
        this->enable();
        this->makeVisible();
        return false;
    };
    EventQueue::addHandler(startNight, handle);
}