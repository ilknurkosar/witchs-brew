#include "DayGui.hpp"
#include "DayTime.hpp"
#include "Global.hpp"
#include "NightGui.hpp"
#include "NightTime.hpp"
#include "Node.hpp"
#include "PotionShop.hpp"
#include "RunnableNode.hpp"
#include "Scene.hpp"
#include <iostream>

std::vector<std::unique_ptr<Resource>> Global::resources{};

void initialize(){
    PotionShop* shop = new PotionShop();
    shop->disable();
    shop->makeInvisible();
    Scene::addNode(shop);

    NightGui *ng = new NightGui();
    NightTime *nt = new NightTime(shop);
    ng->setParent(nt);
    Scene::addNode(nt);
    DayGui *dg = new DayGui();
    DayTime *dt = new DayTime(shop);
    dg->setParent(dt);
    Scene::addNode(dt);
    dt->disable();
    dt->makeInvisible();

    nt->Init(&dt->startNight);
    dt->Init(&nt->startDay);
}