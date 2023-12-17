#pragma once

#include "Renderer.hpp"
#include <memory>

//I should probably implement a singleton template
class MainLoop {
public:
    std::unique_ptr<Renderer> renderer;
    static MainLoop *singleton;
private:
    bool isRunning = false;
public:
    static MainLoop *getSingleton();
    static int Update(double delta, void* data); // Per frame update function.
    MainLoop();   // Allocate resources for runtime
    ~MainLoop(); // Save progress and free resources
};