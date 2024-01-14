#pragma once

#include <map>
#include <functional>
#include "Runnable.hpp"
#include "Event.hpp"

// Namespace for input-related events
namespace InputEvent {
    enum ENUM {
        KEY_UP,
        KEY_DOWN,
        KEY_RIGHT,
        KEY_LEFT,
        KEY_W,
        KEY_A,
        KEY_S,
        KEY_D
    };
};

// InputHandle class, derived from the Runnable interface
class InputHandle : public Runnable {
private:
    static InputHandle* singleton;
    std::map<int, Event> keyMap; // Map to store key mappings

public:
    // Constructor
    InputHandle();

    // Destructor
    ~InputHandle();

    // Implementation of the process function from the Runnable interface
    virtual void process() override;

    // Static method to map a key to an input event
    static void mapKey(int keyCode, InputEvent::ENUM eventType);

    // Static method to unmap a key
    static void unmapKey(int keyCode);

    // Static method to clear all key mappings
    static void clearKeyMappings();
};



