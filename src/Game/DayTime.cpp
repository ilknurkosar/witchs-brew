#include "DayTime.hpp"
#include "EventQueue.hpp"
#include "PotionShop.hpp"
DayTime::DayTime(PotionShop* shop)
: shop(shop) , startNight(500)
{

}

void DayTime::process(){
    
}
void DayTime::endDay(){
    EventQueue::fireEvent(startNight, 0);
    disable();
    makeInvisible();
}

void DayTime::Init(void* data){
    Event startDay = *((Event*)data);
    EventHandler handle = [this](void* x)-> bool{
        this->enable();
        this->makeVisible();
        return false;
    };
    EventQueue::addHandler(startDay, handle);
}