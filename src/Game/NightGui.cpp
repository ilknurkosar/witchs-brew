#include "NightGui.hpp"
#include "Global.hpp"
#include "raylib.h"
#include "raymath.h"
#include <iostream>
NightGui::NightGui() : boxes() {
  boxes.push_back(::Rectangle{25, 25, 750, 400});
  boxes.push_back(::Rectangle{15, 15, 770, 420});
  boxes.push_back(::Rectangle{800-135, 450-95, 100, 60});
  // t = MatrixTranslate(25,25,0);
}

void NightGui::display(Matrix transform) {
  std::vector<::Rectangle> tBoxes = transformBoxes(transform);
  DrawRectangleRec(tBoxes[1], Fade(RED, 0.1));
  raygui::GuiSetStyle(raygui::DEFAULT, raygui::TEXT_SIZE, 40);
  raygui::GuiGroupBox(tBoxes[0], "the shop");
  raygui::GuiSetStyle(0, 0, 0);
  raygui::GuiSetStyle(raygui::DEFAULT, raygui::TEXT_SIZE, 10);
  int ret = raygui::GuiButton(tBoxes[2], "Show FPS");
  if(ret)
    Global::showStats ^=1;
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