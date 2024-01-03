#pragma once

#include "Renderer.hpp"
#include "Scene.hpp"
#include "Vector2.hpp"
#include "Window.hpp"
#include <memory>

//Intentionally didn't implement a singleton baseclass.
class MainLoop {
public:
    std::unique_ptr<raylib::Window> window;
    std::unique_ptr<Scene> scene;
    std::unique_ptr<Renderer> renderer;
    static MainLoop *singleton;
    raylib::Vector2 screenDim = {800,450};
private:
    bool isRunning = false;
public:
    static MainLoop *getSingleton();
    static void Update(); // Per frame update function.
    MainLoop();   // Allocate resources for runtime
    ~MainLoop(); // Save progress and free resources
};