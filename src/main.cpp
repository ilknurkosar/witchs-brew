#include "Camera3D.hpp"
#include "RenderTexture.hpp"
#include "Shader.hpp"
#include "Vector3.hpp"
#include "raylib.h"
#include "rlgl.h"
#include <raylib-cpp.hpp>

#include <emscripten/emscripten.h>

// TARGET ONLY WEB
// #if defined(PLATFORM_DESKTOP)
//    #define GLSL_VERSION            330
// #else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
// #endif

static RenderTexture2D LoadRenderTextureDepthTex(int width, int height);
static void UnloadRenderTextureDepthTex(RenderTexture2D target);
static void UpdateDrawFrame(void *arg); // Update and draw one frame

// unnamed Namespace (identical to static in C)
// makes it so the contents of this namespace is local to this
// translation-unit(the .cpp file)
namespace {
struct RayLocs {
  int camPos, camDir, screenCenter;
};
} // namespace

static const int screenWidth = 800;
static const int screenHeight = 450;
int main(void) {

  // Initialization
  //--------------------------------------------------------------------------------------

  raylib::Window window(screenWidth, screenHeight,
                        "raylib [shaders] example - Hybrid render");

  // Load shader and setup location points and values
  raylib::Shader shader_raymarch(
      NULL,
      TextFormat("resources/shaders/glsl%i/hybrid_raymarch.fs", GLSL_VERSION));
  raylib::Shader shader_raster(
      0, TextFormat("resources/shaders/glsl%i/hybrid_raster.fs", GLSL_VERSION));

  RayLocs locs_raymarch{.camPos = shader_raymarch.GetLocation("camPos"),
                        .camDir = shader_raymarch.GetLocation("camDir"),
                        .screenCenter =
                            shader_raymarch.GetLocation("screenCenter")};

  Vector2 screenCenter = {.x = screenWidth / 2.0, .y = screenHeight / 2.0};
  shader_raymarch.SetValue(locs_raymarch.screenCenter, &screenCenter,
                           SHADER_UNIFORM_VEC2);

  // Use Customized function to create writable depth texture buffer
  RenderTexture2D target = LoadRenderTextureDepthTex(screenWidth, screenHeight);

  raylib::Camera camera{
      Vector3{0.5f, 1.0f, 1.5f}, // Camera position
      Vector3{0.0f, 0.5f, 0.0f}, // Camera looking at point
      Vector3{0.0f, 1.0f, 0.0f}, // Camera up vector (rotation towards target)
      45.0f,                     // Camera field-of-view Y
      CAMERA_PERSPECTIVE         // Camera projection type
  };

  DisableCursor(); // Limit cursor to relative movement inside the window
  window.SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  // -------------------------------------------------------------------------------------------------------------
  void *myargs[5] = {
      &shader_raymarch, &shader_raster, &locs_raymarch, &target, &camera,
  };

  emscripten_set_main_loop_arg(UpdateDrawFrame, myargs, 60, true);
  // Main game loop
  while (!window.ShouldClose()) // Detect window close button or ESC key
    UnloadRenderTextureDepthTex(target);
  return 0;
}

static void UpdateDrawFrame(void *arg) {
  void **myargs = (void **)arg;
  static raylib::Shader &shader_raymarch = *(raylib::Shader *)(myargs[0]);
  static raylib::Shader &shader_raster = *(raylib::Shader *)(myargs[1]);
  static RayLocs &locs_raymarch = *(RayLocs *)(myargs[2]);
  static RenderTexture2D &target = *(RenderTexture2D *)(myargs[3]);
  static raylib::Camera &camera = *(raylib::Camera *)(myargs[4]);
  // Camera FOV is pre-calculated in the camera Distance.
  static double camDist = 1.0 / (tan(camera.fovy * 0.5 * DEG2RAD));

  // Update
  //----------------------------------------------------------------------------------
  camera.Update(CAMERA_FIRST_PERSON);

  shader_raymarch.SetValue(locs_raymarch.camPos, &(camera.position),
                           SHADER_UNIFORM_VEC3);

  Vector3 camDir = Vector3Scale(
      Vector3Normalize(Vector3Subtract(camera.target, camera.position)),
      camDist);
  shader_raymarch.SetValue(locs_raymarch.camDir, &camDir, SHADER_UNIFORM_VEC3);
  //----------------------------------------------------------------------------------

  // Draw
  //----------------------------------------------------------------------------------
  // Draw into our custom render texture (framebuffer)
  BeginTextureMode(target);
    ClearBackground(RAYWHITE);

  // Raymarch Scene
    rlEnableDepthTest(); // Manually enable Depth Test to handle multiple
                       // rendering methods.
    shader_raymarch.BeginMode();
      DrawRectangleRec((Rectangle){0, 0, screenWidth, screenHeight}, WHITE);
    EndShaderMode();

    // Raserize Scene
    camera.BeginMode();
      shader_raster.BeginMode();
        DrawCubeWiresV((Vector3){0.0f, 0.5f, 1.0f}, (Vector3){1.0f, 1.0f, 1.0f}, RED);
        DrawCubeV((Vector3){0.0f, 0.5f, 1.0f}, (Vector3){1.0f, 1.0f, 1.0f}, PURPLE);
        DrawCubeWiresV((Vector3){0.0f, 0.5f, -1.0f}, (Vector3){1.0f, 1.0f, 1.0f},
                       DARKGREEN);
        DrawCubeV((Vector3){0.0f, 0.5f, -1.0f}, (Vector3){1.0f, 1.0f, 1.0f}, YELLOW);
        DrawGrid(10, 1.0f);
      EndShaderMode();
    EndMode3D();
  EndTextureMode();

  // Draw to screen
  BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTextureRec(target.texture, (Rectangle){0, 0, screenWidth, -screenHeight},
                   (Vector2){0, 0}, WHITE);
    DrawFPS(10, 10);
  EndDrawing();
  //----------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------------
// Define custom functions required for the example
//------------------------------------------------------------------------------------
// Load custom render texture, create a writable depth texture buffer
static RenderTexture2D LoadRenderTextureDepthTex(int width, int height) {
  RenderTexture2D target = {0};

  target.id = rlLoadFramebuffer(width, height); // Load an empty framebuffer

  if (target.id > 0) {
    rlEnableFramebuffer(target.id);

    // Create color texture (default to RGBA)
    target.texture.id =
        rlLoadTexture(0, width, height, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);
    target.texture.width = width;
    target.texture.height = height;
    target.texture.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
    target.texture.mipmaps = 1;

    // Create depth texture buffer (instead of raylib default renderbuffer)
    target.depth.id = rlLoadTextureDepth(width, height, false);
    target.depth.width = width;
    target.depth.height = height;
    target.depth.format = 19; // DEPTH_COMPONENT_24BIT?
    target.depth.mipmaps = 1;

    // Attach color texture and depth texture to FBO
    rlFramebufferAttach(target.id, target.texture.id,
                        RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_TEXTURE2D,
                        0);
    rlFramebufferAttach(target.id, target.depth.id, RL_ATTACHMENT_DEPTH,
                        RL_ATTACHMENT_TEXTURE2D, 0);

    // Check if fbo is complete with attachments (valid)
    if (rlFramebufferComplete(target.id))
      TRACELOG(LOG_INFO, "FBO: [ID %i] Framebuffer object created successfully",
               target.id);

    rlDisableFramebuffer();
  } else
    TRACELOG(LOG_WARNING, "FBO: Framebuffer object can not be created");

  return target;
}

// Unload render texture from GPU memory (VRAM)
static void UnloadRenderTextureDepthTex(RenderTexture2D target) {
  if (target.id > 0) {
    // Color texture attached to FBO is deleted
    rlUnloadTexture(target.texture.id);
    rlUnloadTexture(target.depth.id);

    // NOTE: Depth texture is automatically
    // queried and deleted before deleting framebuffer
    rlUnloadFramebuffer(target.id);
  }
}