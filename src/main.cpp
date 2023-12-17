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
  MainLoop mainloop{};
  // -------------------------------------------------------------------------------------
  // Main game loop
  #ifdef PLATFORM_WEB
    emscripten_request_animation_frame_loop(MainLoop::Update, 0);
    emscripten_resume_main_loop();
  #else
    while(!window.ShouldClose()){
      MainLoop::Update(0,0);
    }
  #endif
  return 0;
}