#include "EventQueue.hpp"

EventQueue::EventQueue() {}

void EventQueue::addEvent(const Event& event) {
    activeEvents.push_back(event);
}

void EventQueue::addHandler(const Event& event, std::function<bool(void*)> handler) {
    eventHandlers[event.id].push_back(handler);
}

void EventQueue::process(double delta) {
    for (auto& event : activeEvents) {
        if (eventHandlers.find(event.id) != eventHandlers.end()) {
            for (auto& handler : eventHandlers[event.id]) {
                if (!handler(reinterpret_cast<void*>(&event))) {
                    break;
                }
            }
        }
    }
    activeEvents.clear();
}
