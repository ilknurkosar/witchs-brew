#include "NightGui.hpp"
#include "Global.hpp"
#include "InfiniteShop.hpp"
#include "NightTime.hpp"
#include "PotionShop.hpp"
#include "TradeAgent.hpp"
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>
#include <vector>
#include "raygui-implement.h"

static std::vector<std::string> createLabelList(std::vector<Item> &items, TradeAgent *agent){
  std::vector<std::string> out{};
  for (Item item : items) {
    std::string temp{agent->getLabel(item)};
    float price = agent->getDemand(item).second;
    temp +=  TextFormat(" - %s  ",price == 0 ? "FREE" : TextFormat("%.1f $",price));
    out.push_back(temp);
  }
  return out;
}

static inline void DrawUpgradeMenu(const std::vector<Rectangle> &bounds, PotionShop* shop){
  raygui::GuiSetAlpha(0.7f);
  raygui::setFontSize(30);
  InfiniteShop* upgShop = shop->getUpgradeShop();

  //list of upgrades
  auto upgrades = upgShop->GetAvailableItems();
  auto upgradeNames = createLabelList(upgrades, shop->getUpgradeShop());
  const char* upgradeList[upgrades.size()];
  for (int i=0; i<upgrades.size(); i++) {
    upgradeList[i]=upgradeNames[i].c_str();
  }
  static int upgradeIndex = 0;
  static int upgradeActive = -1;
  static int upgradeFocus = -1;
  raygui::GuiSetState(raygui::STATE_FOCUSED);
  raygui::GuiSetStyle(raygui::LISTVIEW, raygui::TEXT_ALIGNMENT, raygui::TEXT_ALIGN_RIGHT);
  raygui::GuiSetStyle(raygui::LISTVIEW, raygui::TEXT_PADDING, 10);
  raygui::GuiListViewEx(bounds[5], upgradeList, upgradeNames.size(), &upgradeIndex, &upgradeActive, &upgradeFocus);
  raygui::GuiSetStyle(raygui::LISTVIEW, raygui::TEXT_ALIGNMENT, raygui::TEXT_ALIGN_CENTER);
  raygui::GuiSetState(raygui::STATE_NORMAL);

  //Description
  raygui::GuiSetStyle(raygui::DEFAULT, raygui::TEXT_ALIGNMENT_VERTICAL, raygui::TEXT_ALIGN_TOP);
  raygui::GuiSetStyle(raygui::DEFAULT, raygui::TEXT_ALIGNMENT, raygui::TEXT_ALIGN_LEFT);
  raygui::GuiSetStyle(raygui::DEFAULT, raygui::TEXT_WRAP_MODE, raygui::TEXT_WRAP_WORD);
  std::string desc{};
  if(upgradeActive != -1)
    desc = upgShop->getDesc(upgrades[upgradeActive]);
  raygui::GuiSetState(raygui::STATE_FOCUSED);
  raygui::GuiTextBox(bounds[6], (char*)desc.c_str(), 20, false);
  raygui::GuiSetState(raygui::STATE_NORMAL);
  raygui::GuiSetStyle(raygui::DEFAULT, raygui::TEXT_ALIGNMENT_VERTICAL, raygui::TEXT_ALIGN_MIDDLE);
  raygui::GuiSetStyle(raygui::DEFAULT, raygui::TEXT_ALIGNMENT, raygui::TEXT_ALIGN_CENTER);
  raygui::GuiSetStyle(raygui::DEFAULT, raygui::TEXT_WRAP_MODE, raygui::TEXT_WRAP_NONE);

  raygui::GuiSetAlpha(1.0);
}

NightGui::NightGui() : boxes() {
  boxes.push_back(::Rectangle{25, 25, 750, 400}); //background rectangle
  boxes.push_back(::Rectangle{15, 15, 770, 420}); //inner encapsulating rectangle
  boxes.push_back(::Rectangle{800-170, 450-70, 130, 30}); //Price selector
  boxes.push_back(::Rectangle{800-170, 450-110, 130, 30});//Day starter
  boxes.push_back(::Rectangle{25, 325, 750, 100}); // bottom half
  boxes.push_back(::Rectangle{35, 55, 730, 250}); // upgrade list
  boxes.push_back(::Rectangle{35, 340, 570, 70}); // description box
  // boxes.push_back(::Rectangle{800-170, 450-150, 130, 30});
  // t = MatrixTranslate(25,25,0);
}

void NightGui::display(Matrix transform) {
  raygui::setStyle(raygui::STYLE_CHERRY);
  std::vector<::Rectangle> tBoxes = transformBoxes(transform);
  const Color col{raygui::getStyleColor()};
  const float alpha = 0.90;
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

  int price = shop->getPrice();
  int newprice = price;
  static bool priceEdit = false;
  priceEdit ^= raygui::GuiSpinner(tBoxes[2], nullptr, &newprice, 0, 100, priceEdit);
  if(newprice != price)
    shop->setPrice(static_cast<float>(newprice));

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