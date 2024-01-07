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

static std::vector<const char*> createLabelList(std::vector<Item> &items, TradeAgent *agent){
  std::vector<const char*> out{};
  for (Item item : items) {
    out.push_back(agent->getLabel(item).c_str());
  }
  return out;
}

static inline void DrawUpgradeMenu(const std::vector<Rectangle> &bounds, PotionShop* shop){
  int price = shop->getPrice();
  int newprice = price;
  static bool priceEdit = false;
  priceEdit ^= raygui::GuiSpinner(bounds[2], nullptr, &newprice, 0, 100, priceEdit);
  if(newprice != price)
    shop->setPrice(static_cast<float>(newprice));

  auto upgrades = shop->getUpgradeShop()->GetAvailableItems();
  auto upgradeNames = createLabelList(upgrades, shop->getUpgradeShop());
  static int upgradeIndex = 0;
  static int upgradeActive = -1;
  static int upgradeFocus = -1;
  raygui::GuiSetState(raygui::STATE_FOCUSED);
  raygui::GuiListViewEx(bounds[5], upgradeNames.data(), upgradeNames.size(), &upgradeIndex, &upgradeActive, &upgradeFocus);
  raygui::GuiSetState(raygui::STATE_NORMAL);
}

NightGui::NightGui() : boxes() {
  boxes.push_back(::Rectangle{25, 25, 750, 400}); //background rectangle
  boxes.push_back(::Rectangle{15, 15, 770, 420}); //inner encapsulating rectangle
  boxes.push_back(::Rectangle{800-170, 450-70, 130, 30});
  boxes.push_back(::Rectangle{800-170, 450-110, 130, 30});
  boxes.push_back(::Rectangle{25, 325, 750, 100});
  boxes.push_back(::Rectangle{35, 45, 100, 250});
  // boxes.push_back(::Rectangle{800-170, 450-150, 130, 30});
  // t = MatrixTranslate(25,25,0);
}

void NightGui::display(Matrix transform) {
  raygui::setStyle(raygui::STYLE_CHERRY);
  std::vector<::Rectangle> tBoxes = transformBoxes(transform);
  const Color col{raygui::getStyleColor()};
  const float alpha = 0.95;
  PotionShop *shop = static_cast<NightTime*>(parent)->getShop();
  float balance = shop->getBalance();
  DrawRectangleRec(tBoxes[1], Fade(col, alpha));
  DrawRectangleRec(tBoxes[4], ColorAlphaBlend(RAYWHITE, Fade(col, alpha), WHITE));
  raygui::setFontSize(40);
  raygui::GuiGroupBox(tBoxes[0], "the shop");
  raygui::setFontSize(20);
  int ret = raygui::GuiButton(tBoxes[3], "end Night");
  if(ret)
    static_cast<NightTime*>(parent)->endNight();
  raygui::GuiGroupBox(tBoxes[4],TextFormat("Money%10.1f",balance));

  // static int style = 0;
  // raygui::GuiComboBox(tBoxes[6], "Default;Ashes;Bluish;Candy;Cherry;Cyber;Dark;Enefete;Jungle;Lavanda;Sunny;Terminal", &style);

  DrawUpgradeMenu(tBoxes, shop);
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