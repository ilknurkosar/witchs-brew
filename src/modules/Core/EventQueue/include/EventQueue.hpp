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

    //TODO: this is supposed to be a priority queue
    std::map<Event, std::vector<EventHandler>> eventHandlers;
    std::vector<std::pair<Event, void*>> activeEvents;

public:
    EventQueue();
    ~EventQueue();

    static inline EventQueue* getSingleton(){return singleton;}
    static inline void fireEvent(Event event, void* data){singleton->activeEvents.push_back({event,data});}
    static void addHandler(Event event, EventHandler handler); //events are added only after they get a corresponding handler
    void process() override;
private:
    void addEvent(Event e);
};
