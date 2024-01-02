#include "Global.hpp"
#include "NightGui.hpp"
#include "Scene.hpp"
#include <iostream>

std::vector<std::unique_ptr<Resource>> Global::resources{};

void initialize(){
    NightGui *ng = new NightGui();
    Scene::addNode(ng);
}