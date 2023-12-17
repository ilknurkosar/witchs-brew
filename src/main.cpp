#include "MainLoop.hpp"
#include "Window.hpp"
#include "raylib.h"


#ifdef PLATFORM_WEB
  #include <emscripten/emscripten.h>
  #include "emscripten/html5.h"
#endif

static const Vector2 screenDim = {800, 450};
int main(void) {

  // Initialization
  //--------------------------------------------------------------------------------------
  raylib::Window window(screenDim.x,screenDim.y,
                        "raylib [shaders] example - Hybrid render");

  SetTraceLogLevel(LOG_DEBUG);

  DisableCursor(); // Limit cursor to relative movement inside the window
  // window.SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  MainLoop mainloop{};
  // -------------------------------------------------------------------------------------------------------------
  // Main game loop
  #ifdef PLATFORM_WEB
    emscripten_request_animation_frame_loop(MainLoop::Update, 0);
    emscripten_resume_main_loop();
  #else
    while(!window.ShouldClose()){
      UpdateDrawFrame();
    }
  #endif
  return 0;
}