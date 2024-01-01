#pragma once

#include <vector>
#include <functional>
#include <map>

struct Event {
    int id;
};

class EventQueue {
private:
    std::map<int, std::vector<std::function<bool(void*)>>> eventHandlers; 
    std::vector<Event> activeEvents;

public:
    EventQueue();

    void addEvent(const Event& event);
    void addHandler(const Event& event, std::function<bool(void*)> handler);
    void process(double delta);
};
