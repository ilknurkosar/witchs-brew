#include "GuiButton.hpp"

void GuiButton::display(Matrix transform){
    bool pressed = raygui::GuiButton(shape, message.c_str());
    if(pressed & (handler != nullptr))
        handler();
}