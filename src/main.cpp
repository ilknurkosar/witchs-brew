#include "MainLoop.hpp"
#include "Window.hpp"
#include "raylib.h"


#ifdef PLATFORM_WEB
  #include <emscripten/emscripten.h>
  #include "emscripten/html5.h"
#endif

static const Vector2 screenDim = {800, 450};

/**
 * @brief Entry point of the whole program. End-user is not supposed to interact with this.
 * 
 * @return int 
 */
int main(void) {

  bool isRunning = true;
  // Initialization
  //--------------------------------------------------------------------------------------
  MainLoop mainloop{};
  // -------------------------------------------------------------------------------------
  // Main game loop
  #ifdef PLATFORM_WEB
    emscripten_set_main_loop(MainLoop::Update, 0, true);
    // emscripten_request_animation_frame_loop(MainLoop::Update, 0);
  #else
    while(!WindowShouldClose()){
      MainLoop::Update();
    }
  #endif
  return 0;
}