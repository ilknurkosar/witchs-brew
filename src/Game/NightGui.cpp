#include "NightGui.hpp"
#include "Global.hpp"
#include "NightTime.hpp"
#include "PotionShop.hpp"
#include "TradeAgent.hpp"
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector>
#include "raygui-implement.h"

NightGui::NightGui() : boxes() {
  boxes.push_back(::Rectangle{25, 25, 750, 400});
  boxes.push_back(::Rectangle{15, 15, 770, 420});
  boxes.push_back(::Rectangle{800-140, 450-70, 100, 30});
  boxes.push_back(::Rectangle{800-140, 450-110, 100, 30});
  boxes.push_back(::Rectangle{25, 325, 750, 100});
  boxes.push_back(::Rectangle{35, 45, 100, 250});
  // t = MatrixTranslate(25,25,0);
}

static std::vector<const char*> createLabelList(std::vector<Item> &items, TradeAgent *agent){
  std::vector<const char*> out{};
  for (Item item : items) {
    out.push_back(agent->getLabel(item).c_str());
  }
  return out;
}

void NightGui::display(Matrix transform) {
  std::vector<::Rectangle> tBoxes = transformBoxes(transform);
  const Color col{255, 220, 220, 255};
  const float alpha = 0.95;
  PotionShop *shop = static_cast<NightTime*>(parent)->getShop();
  float balance = shop->getBalance();
  DrawRectangleRec(tBoxes[1], Fade(col, alpha));
  DrawRectangleRec(tBoxes[4], ColorAlphaBlend(RAYWHITE, Fade(col, alpha), WHITE));
  raygui::GuiSetStyle(raygui::DEFAULT, raygui::TEXT_SIZE, 40);
  raygui::GuiGroupBox(tBoxes[0], "the shop");
  raygui::GuiSetStyle(0, 0, 0);
  raygui::GuiSetStyle(raygui::DEFAULT, raygui::TEXT_SIZE, 10);
  int ret = raygui::GuiButton(tBoxes[3], "end Night");
  if(ret)
    static_cast<NightTime*>(parent)->endNight();
  raygui::GuiSetStyle(raygui::DEFAULT, raygui::TEXT_SIZE, 20);
  raygui::GuiGroupBox(tBoxes[4],TextFormat("Money%10.1f",balance));
  int price = shop->getPrice();
  int newprice = price;
  static bool priceEdit = false;
  priceEdit ^= raygui::GuiSpinner(tBoxes[2], nullptr, &newprice, 0, 100, priceEdit);
  if(newprice != price)
    shop->setPrice(static_cast<float>(newprice));
  {
    auto upgrades = shop->getUpgradeShop()->GetAvailableItems();
    auto upgradeNames = createLabelList(upgrades, shop->getUpgradeShop());
    static int upgradeIndex = 0;
    static int upgradeActive = -1;
    static int upgradeFocus = -1;
    raygui::GuiListViewEx(tBoxes[5], upgradeNames.data(), upgradeNames.size(), &upgradeIndex, &upgradeActive, &upgradeFocus);
  }
}

std::vector<::Rectangle> NightGui::transformBoxes(Matrix m) {
  std::vector<::Rectangle> out{};
  for (Rectangle r : boxes) {
    Vector2 p{r.x, r.y};          // position
    Vector2 d{r.width, r.height}; // dimension
    p = Vector2Transform(p, t);
    m.m12 = 0;
    m.m13 = 0;
    d = Vector2Transform(d, m);
    out.push_back(::Rectangle{p.x, p.y, d.x, d.y});
  }
  return out;
}