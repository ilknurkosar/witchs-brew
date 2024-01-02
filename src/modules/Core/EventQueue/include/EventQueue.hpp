#pragma once

#include "Runnable.hpp"
#include <memory>
#include <utility>
#include <vector>
#include <map>
#include "Event.hpp"


class EventQueue : public Runnable {
private:
    static EventQueue* singleton;
    std::map<Event, std::unique_ptr<std::vector<bool(*)(void*)>>> eventHandlers; 
    std::vector<std::pair<Event, void*>> activeEvents;

public:
    EventQueue();
    ~EventQueue();

    static inline EventQueue* getSingleton(){return singleton;}
    static inline void fireEvent(Event event, void* data){singleton->activeEvents.push_back({event,data});}
    static void addHandler(Event event, bool(*handler)(void*)); //events are added only after they get a corresponding handler
    void process(double delta) override;
};
