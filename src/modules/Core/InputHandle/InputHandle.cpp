#include "InputHandle.hpp"

InputHandle::InputHandle() {
    keyMap[KEY_UP] = EventType::KEY_PRESS;
    keyMap[KEY_DOWN] = EventType::KEY_PRESS;
    keyMap[KEY_RIGHT] = EventType::KEY_PRESS;
    keyMap[KEY_LEFT] = EventType::KEY_PRESS;
    keyMap[KEY_W] = EventType::KEY_PRESS;
    keyMap[KEY_A] = EventType::KEY_PRESS;
    keyMap[KEY_S] = EventType::KEY_PRESS;
    keyMap[KEY_D] = EventType::KEY_PRESS;

    
}

void InputHandle::setEventCallback(std::function<void(Event)> callback) {
    eventCallback = callback;
}

void InputHandle::processInput() {
    processMouseInput();
    processKeyboardInput();
}

void InputHandle::processMouseInput() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        handleEvent(EventType::CLICK);
    }
}

void InputHandle::processKeyboardInput() {
    for (const auto& keyPair : keyMap) {
        if (IsKeyPressed(keyPair.first)) {
            handleEvent(keyPair.second);
        }
    }
}

void InputHandle::handleEvent(EventType eventType) {

    Event event{ eventType };
    if (eventCallback) {
        eventCallback(event);
    }
}

void InputHandle::mapKey(int keyCode, EventType eventType) {
    keyMap[keyCode] = eventType;
}

void InputHandle::unmapKey(int keyCode) {
    keyMap.erase(keyCode);
}

void InputHandle::clearKeyMappings() {
    keyMap.clear();
}
