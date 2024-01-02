#include "EventQueue.hpp"
#include <utility>

EventQueue* EventQueue::singleton = nullptr;

EventQueue::EventQueue() {
    singleton = this;
}
EventQueue::~EventQueue() {
    singleton = nullptr;
}

void EventQueue::addHandler(Event event, bool(*handler)(void*)) {
    if(handler)
        singleton->eventHandlers[event]->push_back(handler);
}

void EventQueue::process(double delta) {
    for (auto& payload : activeEvents) {
        if (eventHandlers.find(payload.first) != eventHandlers.end()) {
            for (auto& handler : *eventHandlers[payload.first]) {
                if (!handler(payload.second)) {
                    break;
                }
            }
        }
    }
    activeEvents.clear();
}
