#pragma once



#include "raylib.h"
#if defined(__cplusplus)
namespace raygui {
    #include "raygui.h"
#else
    #include "raygui.h"
#endif
#if defined(__cplusplus)
extern "C" {            // Prevents name mangling of functions
#endif

typedef enum
{
    STYLE_DEFAULT,
    STYLE_ASHES,
    STYLE_BLUISH,
    STYLE_CANDY,
    STYLE_CHERRY,
    STYLE_CYBER,
    STYLE_DARK,
    STYLE_ENEFETE,
    STYLE_JUNGLE,
    STYLE_LAVANDA,
    STYLE_SUNNY,
    STYLE_TERMINAL
}GUI_STYLE;

Color getStyleColor();
void setStyle(GUI_STYLE styleId);

#if defined(__cplusplus)
}}
#endif