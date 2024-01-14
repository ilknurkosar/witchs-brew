#pragma once

#include "Runnable.hpp"
#include <memory>
#include <utility>
#include <vector>
#include <map>
#include "Event.hpp"

// Constructor
class EventQueue : public Runnable {
private:
    static EventQueue* singleton;

    //TODO: this is supposed to be a priority queue
    std::map<Event, std::vector<EventHandler>> eventHandlers;
    std::vector<std::pair<Event, void*>> activeEvents;

public// Constructor
    EventQueue();

    // Destructor
    ~EventQueue();
 // Getter for the singleton instance
    static inline EventQueue* getSingleton() { return singleton; }

    // Static method to fire an event
    static inline void fireEvent(Event event, void* data) { singleton->activeEvents.push_back({event, data}); }

    // Static method to add an event handler
    static void addHandler(Event event, EventHandler handler); // Events are added only after they get a corresponding handler

    // Implementation of the process function from the Runnable interface
    void process() override;

private:
    // Private method to add an event to the active events list
    void addEvent(Event e);
};
