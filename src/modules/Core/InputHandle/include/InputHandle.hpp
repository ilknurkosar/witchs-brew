#pragma once

#include <map>
#include <functional>
#include "Runnable.hpp"
#include "Event.hpp"

namespace InputEvent{
    enum ENUM{
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

class InputHandle : public Runnable {
private:
    static InputHandle* singleton;
    std::map<int, Event> keyMap;

public:
    InputHandle();
    ~InputHandle();

    virtual void process() override;

    static void mapKey(int keyCode, InputEvent::ENUM eventType);

    static void unmapKey(int keyCode);

    static void clearKeyMappings();

};


