#include "Event.hpp"
#include "EventQueue.hpp"
#include "gtest/gtest.h"
#include <gtest/gtest.h>

TEST(Event, single_event){
    int i = 1;
    EventQueue eq{};
    Event e = 1;
    const EventHandler handle = [](void* x)->bool{
        *static_cast<int*>(x) = 2;
        return true;
    };
    EventQueue::addHandler(e, handle);
    EventQueue::fireEvent(e, &i);
    eq.process();
    ASSERT_EQ(i, 2);
}

TEST(Event, local_ref){
    struct mock{
        int i = 0;
        mock(){
            EventHandler handle = [this](void* x){
                this->i++;
                return true;
            };
            EventQueue::addHandler(1, handle);
        }
    };
    EventQueue q{};
    mock m{};
    EventQueue::fireEvent(1, 0);
    q.process();
    ASSERT_EQ(m.i, 1);
}