#include "GuiButton.hpp"
#include "GuiCheckBox.hpp"

void GuiCheckBox::display(Matrix transform){
    bool old = pressed;
    raygui::GuiCheckBox(shape, message.c_str(), &pressed);
    bool changed = old ^ pressed;
    if(changed & (handler != nullptr))
        handler(pressed);
}