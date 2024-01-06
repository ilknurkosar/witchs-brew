#include "DayGui.hpp"
#include "DayTime.hpp"
#include "Global.hpp"
#include "InfiniteShop.hpp"
#include "NightGui.hpp"
#include "NightTime.hpp"
#include "Node.hpp"
#include "PotionShop.hpp"
#include "RunnableNode.hpp"
#include "Scene.hpp"
#include <iostream>

std::vector<std::unique_ptr<Resource>> Global::resources{};

void initialize(){
    PotionShop* shop = new PotionShop(500.0);
    shop->disable();
    shop->makeInvisible();
    Scene::addNode(shop);
    InfiniteShop *upgrade =shop->getUpgradeShop();
    InfiniteShop *ingredient =shop->getIngredientShop();
    shop->appendItem(Item::POTION, 500.0f, "Potion");
    shop->setPrice(5.0f);

    Item U_nice = {500};
    upgrade->AddItem(U_nice, 10.0, "Be nicer");

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