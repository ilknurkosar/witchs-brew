#include "NightGui.hpp"
#include "raylib.h"
#include "raymath.h"
#include <iostream>
NightGui::NightGui() : boxes() {
  boxes.push_back(::Rectangle{0, 0, 100, 40});
  // t = MatrixTranslate(20,150,0);
}

void NightGui::display(Matrix transform) {
  std::vector<::Rectangle> tBoxes = transformBoxes();
  raygui::GuiPanel(tBoxes[0], "I am a box.");
}

std::vector<::Rectangle> NightGui::transformBoxes() {
  std::vector<::Rectangle> out{};
  for (Rectangle r : boxes) {
    Vector2 p{r.x, r.y};          // position
    Vector2 d{r.width, r.height}; // dimension
    p = Vector2Transform(p, t);
    Matrix m = t;
    m.m12 = 0;
    m.m13 = 0;
    d = Vector2Transform(d, m);
    out.push_back(::Rectangle{p.x, p.y, d.x, d.y});
  }
  return out;
}