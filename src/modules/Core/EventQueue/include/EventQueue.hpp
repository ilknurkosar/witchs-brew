#pragma once

#include "Runnable.hpp"
#include <utility>
#include <vector>
#include <functional>
#include <map>
#include "Event.hpp"


class EventQueue : public Runnable {
private:
    static EventQueue* singleton;
    std::map<Event, std::vector<std::function<bool(void*)>>> eventHandlers; 
    std::vector<std::pair<Event, void*>> activeEvents;

public:
    EventQueue();
    ~EventQueue();

    static inline EventQueue* getSingleton(){return singleton;}
    static inline void fireEvent(Event event, void* data){singleton->activeEvents.push_back({event,data});}
    static void addHandler(Event event, std::function<bool(void*)> handler); //events are added only after they get a corresponding handler
    void process(double delta) override;
};
