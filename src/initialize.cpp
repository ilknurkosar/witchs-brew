#include "DayGui.hpp"
#include "DayTime.hpp"
#include "Global.hpp"
#include "NightGui.hpp"
#include "NightTime.hpp"
#include "Scene.hpp"
#include <iostream>

std::vector<std::unique_ptr<Resource>> Global::resources{};

void initialize(){
    NightGui *ng = new NightGui();
    // NightTime *nt = new NightTime();
    // ng->setParent(nt);
    // Scene::addNode(nt);
    // DayGui *dg = new DayGui();
    // DayTime *dt = new DayTime();
    // dg->setParent(dt);
    // Scene::addNode(dt);
    // dt->disable();
    // dt->makeInvisible();
    Scene::addNode(ng);
}