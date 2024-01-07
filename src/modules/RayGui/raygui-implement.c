#include "raygui-implement.h"
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "ashes/style_ashes.h"
#include "bluish/style_bluish.h"
#include "candy/style_candy.h"
#include "cherry/style_cherry.h"
#include "cyber/style_cyber.h"
#include "dark/style_dark.h"
#include "enefete/style_enefete.h"
#include "jungle/style_jungle.h"
#include "lavanda/style_lavanda.h"
#include "sunny/style_sunny.h"
#include "terminal/style_terminal.h"

Color getStyleColor(){
    return GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR));
}

void setFontSize(int size){
    GuiSetStyle(DEFAULT, TEXT_SIZE , size);
}

void setStyle(GUI_STYLE styleId){
    static GUI_STYLE oldStyle = -1;
    if(oldStyle == styleId)
        return;
    oldStyle = styleId;
    switch (styleId) {
        case STYLE_DEFAULT: GuiLoadStyleDefault(); break;// Default style
        case STYLE_ASHES: GuiLoadStyleAshes(); break;
        case STYLE_BLUISH: GuiLoadStyleBluish(); break;
        case STYLE_CANDY: GuiLoadStyleCandy(); break;
        case STYLE_CHERRY: GuiLoadStyleCherry(); break;
        case STYLE_CYBER: GuiLoadStyleCyber(); break;
        case STYLE_DARK: GuiLoadStyleDark(); break;
        case STYLE_ENEFETE: GuiLoadStyleEnefete(); break;
        case STYLE_JUNGLE: GuiLoadStyleJungle(); break;
        case STYLE_LAVANDA: GuiLoadStyleLavanda(); break;
        case STYLE_SUNNY: GuiLoadStyleSunny(); break;
        case STYLE_TERMINAL: GuiLoadStyleTerminal(); break;
        default: break;
    }
}