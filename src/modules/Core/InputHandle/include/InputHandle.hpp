#pragma once

#include <map>
#include <functional>
#include "raylib.h"

enum class EventType {
    CLICK,
    KEY_PRESS
};

struct Event {
    EventType type;
};

class InputHandle {
private:
    std::map<int, EventType> keyMap;
    std::function<void(Event)> eventCallback;

public:
    InputHandle();

    void setEventCallback(std::function<void(Event)> callback);

    void processInput();

    void processMouseInput();

    void processKeyboardInput();

    void handleEvent(EventType eventType);

    void mapKey(int keyCode, EventType eventType);

    void unmapKey(int keyCode);

    void clearKeyMappings();

};


