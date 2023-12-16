#include "MainLoop.hpp"
#include "raylib.h"

static int initalized = false;

void MainLoop::Init(){
    if(initalized) return;
#ifndef NDEBUG
    SetTraceLogLevel(LOG_DEBUG);
#endif // !NDEBUG

    return;
}
int MainLoop::Update(double delta, void* data){
    if(!initalized) return initalized; // QUIT PROGRAM IF NOT INITIALIZED

    return initalized;
}
void MainLoop::DeInit(){ // WONT RUN IN WEB. The default is to abort code mid-execution if page closes
    if(!initalized) return;
    return;
}