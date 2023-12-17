#include "MainLoop.hpp"
#include "RendererPrototype.hpp"
#include "raylib.h"
#include <memory>

MainLoop *MainLoop::singleton = nullptr;

MainLoop::MainLoop(){
#ifndef NDEBUG
    SetTraceLogLevel(LOG_DEBUG);
#endif // !NDEBUG
    isRunning = true;
    singleton = this;
    renderer = std::make_unique<RendererPrototype>();
    return;
}
int MainLoop::Update(double delta, void* data){
    singleton->renderer->Process(delta);
    return singleton->isRunning;
}
MainLoop::~MainLoop(){ // WONT RUN IN WEB. The default is to abort code mid-execution if page closes
    singleton = nullptr;
    return;
}

MainLoop* MainLoop::getSingleton(){
    return singleton;
}