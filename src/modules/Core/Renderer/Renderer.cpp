#include "Renderer.hpp"

Renderer *Renderer::singleton = nullptr;

Renderer* Renderer::getSingleton(){
    return singleton;
}

Renderer::Renderer(){
    singleton = this;
}
Renderer::~Renderer(){
    singleton = nullptr;
}