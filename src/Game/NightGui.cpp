#include "NightGui.hpp"
#include "Global.hpp"
#include "NightTime.hpp"
#include "raylib.h"
#include "raymath.h"
#include <iostream>

NightGui::NightGui() : boxes() {
  boxes.push_back(::Rectangle{25, 25, 750, 400});
  boxes.push_back(::Rectangle{15, 15, 770, 420});
  boxes.push_back(::Rectangle{800-140, 450-70, 100, 30});
  boxes.push_back(::Rectangle{800-140, 450-110, 100, 30});
  boxes.push_back(::Rectangle{25, 325, 750, 100});
  // t = MatrixTranslate(25,25,0);
}

void NightGui::display(Matrix transform) {
  std::vector<::Rectangle> tBoxes = transformBoxes(transform);
  const Color col{255, 200, 200, 255};
  const float alpha = 0.4;
  DrawRectangleRec(tBoxes[1], Fade(col, alpha));
  DrawRectangleRec(tBoxes[4], ColorAlphaBlend(RAYWHITE, Fade(col, alpha), WHITE));
  raygui::GuiSetStyle(raygui::DEFAULT, raygui::TEXT_SIZE, 40);
  raygui::GuiGroupBox(tBoxes[0], "the shop");
  raygui::GuiSetStyle(0, 0, 0);
  raygui::GuiSetStyle(raygui::DEFAULT, raygui::TEXT_SIZE, 10);
  int ret = raygui::GuiButton(tBoxes[2], "Show FPS");
  if(ret)
    Global::showStats ^=1;
  ret = raygui::GuiButton(tBoxes[3], "end Night");
  if(ret)
    static_cast<NightTime*>(parent)->endNight();
  // static char mytext[128] = "idkman";
  // static bool edited = false;
  // edited ^= raygui::GuiTextBox(tBoxes[4], mytext, 10, edited);
  raygui::GuiSetStyle(raygui::DEFAULT, raygui::TEXT_SIZE, 20);
  float balance = static_cast<NightTime*>(parent)->getShop()->getBalance();
  // std::string msg = std::format("Money: {:10.1}",balance);
  raygui::GuiGroupBox(tBoxes[4],TextFormat("Money%10.1f",balance));
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