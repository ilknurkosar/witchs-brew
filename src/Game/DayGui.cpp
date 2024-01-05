#include "DayGui.hpp"
#include "DayTime.hpp"
#include "Global.hpp"
#include "raylib.h"
#include "raymath.h"
DayGui::DayGui() : boxes() {
  boxes.push_back(::Rectangle{25, 25, 750, 400});
  boxes.push_back(::Rectangle{15, 15, 770, 420});
  boxes.push_back(::Rectangle{800-140, 450-70, 100, 30});
  boxes.push_back(::Rectangle{800-140, 450-110, 100, 30});
  boxes.push_back(::Rectangle{25, 325, 750, 100});
  // t = MatrixTranslate(25,25,0);
}

void DayGui::display(Matrix transform) {
  std::vector<::Rectangle> tBoxes = transformBoxes(transform);
  DrawRectangleRec(tBoxes[1], Fade(PURPLE, 0.1));
  DrawRectangleRec(tBoxes[4], ColorAlphaBlend(RAYWHITE, Fade(PURPLE, 0.1), WHITE));
  raygui::GuiSetStyle(raygui::DEFAULT, raygui::TEXT_SIZE, 40);
  raygui::GuiGroupBox(tBoxes[0], "Sales");
  raygui::GuiSetStyle(0, 0, 0);
  raygui::GuiSetStyle(raygui::DEFAULT, raygui::TEXT_SIZE, 10);
  int ret = raygui::GuiButton(tBoxes[2], "Show FPS");
  if(ret)
    Global::showStats ^=1;
  ret = raygui::GuiButton(tBoxes[3], "end Day");
  if(ret)
    static_cast<DayTime*>(parent)->endDay();
  raygui::GuiSetStyle(raygui::DEFAULT, raygui::TEXT_SIZE, 20);
  float balance = static_cast<DayTime*>(parent)->getShop()->getBalance();
  raygui::GuiGroupBox(tBoxes[4],TextFormat("Money%10.1f",balance));
}

std::vector<::Rectangle> DayGui::transformBoxes(Matrix m) {
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