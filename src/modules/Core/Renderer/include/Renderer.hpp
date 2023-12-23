#pragma once

#include "Runnable.hpp"

// Renderer is a singleton but it has NO mechanisms to enforce it.
// This is done for accessibilty reasons
class Renderer : public Runnable{
public:
    static Renderer *singleton;
public:
    static Renderer *getSingleton();
    Renderer();
    virtual ~Renderer();
};