#include "Camera3D.hpp"
#include "GLES2/gl2.h"
#include "Rectangle.hpp"
#include "RenderTexture.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "customTextures.hpp"
#include "Vector3.hpp"
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <raylib-cpp.hpp>
#include "raylib-wrap.hpp"


#if defined(PLATFORM_DESKTOP)
  #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
  #define GLSL_VERSION 100
  #include <emscripten/emscripten.h>
#endif

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define SHADERS "resources/shaders/glsl" STR(GLSL_VERSION) "/"

static void UpdateDrawFrame(void); // Update and draw one frame

// unnamed Namespace (identical to static in C)
// makes it so the contents of this namespace is local to this
// translation-unit = the .cpp file
namespace {
struct RayLocs {
  int camPos, camDir, screenCenter;
};
} // namespace

static const int screenWidth = 800;
static const int screenHeight = 450;
static const Vector2 screenDim = {screenWidth, screenHeight};
int main(void) {

  // Initialization
  //--------------------------------------------------------------------------------------
  raylib::Window window(screenWidth, screenHeight,
                        "raylib [shaders] example - Hybrid render");

  SetTraceLogLevel(LOG_DEBUG);

  DisableCursor(); // Limit cursor to relative movement inside the window
  window.SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  // -------------------------------------------------------------------------------------------------------------
  // Main game loop
  #ifdef PLATFORM_WEB
    emscripten_set_main_loop(UpdateDrawFrame, 60, true);
  #else
    while(!window.ShouldClose()){
      UpdateDrawFrame();
    }
  #endif
  return 0;
}

static void UpdateDrawFrame(void) {
  static raylib::ShadowTexture target(screenWidth, screenHeight);
  static raylib::Shader shader_shadow(SHADERS "shadow.vs", SHADERS "shadow.fs");
  static raylib::Shader shader_depth(0, SHADERS "depth.fs");
  static raylib::Shader shader_geom(SHADERS "geom.vs", SHADERS "geom.fs");
  static raylib::Shader shader_default(SHADERS "default.vs", SHADERS "default.fs");
  const GLubyte *rendererName= glGetString(GL_RENDERER);

  static raylib::Camera camera{
      Vector3{0.5f, 1.0f, 1.5f}, // Camera position
      Vector3{0.0f, 0.5f, 0.0f}, // Camera looking at point
      Vector3{0.0f, 1.0f, 0.0f}, // Camera up vector (rotation towards target)
      45.0f,                     // Camera field-of-view Y
      CAMERA_PERSPECTIVE         // Camera projection type
  };
  static raylib::Camera light{
      Vector3{9.0f, 2.0f, 5.0f}, // Camera position
      Vector3{0.0f, 1.0f, 0.0f}, // Camera looking at point
      Vector3{0.0f, 1.0f, 0.0f}, // Camera up vector (rotation towards target)
      45.0f,                     // Camera field-of-view Y
      CAMERA_PERSPECTIVE         // Camera projection type
  };
  // Shader locs
  // static int sg_shadow  = GetShaderLocation(shader_geom, "texture1");
  // static int sg_viewPos  = GetShaderLocation(shader_geom, "viewPos");
  // static int sg_matLight = GetShaderLocation(shader_geom, "matLight");
  // static int sg_lightPos = GetShaderLocation(shader_geom, "lightPos");
  // static int sg_lightDir = GetShaderLocation(shader_geom, "lightDir");
  // static int sg_lightCutoff = GetShaderLocation(shader_geom, "lightCutoff");

  static int sd_shadow  =   shader_default.GetLocation("texture1");
  static int sd_ivp  =   shader_default.GetLocation("ivp");
  static int sd_lightMat  =   shader_default.GetLocation("lightMat");
  // Update
  //----------------------------------------------------------------------------------
  camera.Update(CAMERA_FIRST_PERSON);
  light.Update(CAMERA_ORBITAL);

  Matrix lightMat =
    MatrixPerspective(light.fovy*DEG2RAD, double(screenWidth)/double(screenHeight), RL_CULL_DISTANCE_NEAR, RL_CULL_DISTANCE_FAR)
    *
    light.GetMatrix()
    ;
  Matrix ivp =Invert(
    MatrixPerspective(camera.fovy*DEG2RAD, double(screenWidth)/double(screenHeight), RL_CULL_DISTANCE_NEAR, RL_CULL_DISTANCE_FAR)
    *
    camera.GetMatrix()
    );
  Vector3 lightDir = Vector3Normalize(light.position - light.target);
  float cutoff = cosf(DEG2RAD * light.fovy * 0.46f);

  // TODO: fill all uniforms
  // shader_depth.SetValue(sg_viewPos,&(camera.position),SHADER_UNIFORM_VEC3);
  // shader_depth.SetValue(sg_matLight,lightMat);
  // shader_depth.SetValue(sg_viewPos,&(light.position),SHADER_UNIFORM_VEC3);
  // shader_depth.SetValue(sg_lightDir,&lightDir,SHADER_UNIFORM_VEC3);
  // shader_depth.SetValue(sg_lightCutoff,&cutoff,SHADER_UNIFORM_FLOAT);

  shader_default.SetValue(sd_ivp, ivp);
  shader_default.SetValue(sd_lightMat, lightMat);
  //----------------------------------------------------------------------------------

  // Draw
  //----------------------------------------------------------------------------------
  // Draw into our custom render texture (framebuffer)
  target.BeginMode();
    ClearBackground(RED);

    // Raserize Scene
    light.BeginMode();
      shader_shadow.BeginMode();
        DrawCubeWiresV((Vector3){0.0f, 0.5f, 1.0f}, (Vector3){1.0f, 1.0f, 1.0f}, RED);
        DrawCubeV((Vector3){0.0f, 0.5f, 1.0f}, (Vector3){1.0f, 1.0f, 1.0f}, PURPLE);
        DrawCubeWiresV((Vector3){0.0f, 0.5f, -1.0f}, (Vector3){1.0f, 1.0f, 1.0f},
                        DARKGREEN);
        DrawCubeV((Vector3){0.0f, 0.5f, -1.0f}, (Vector3){1.0f, 1.0f, 1.0f}, YELLOW);
        DrawPlane(Vector3{0.0}, Vector2{5.0,5.0}, RED);
        DrawGrid(10, 1.0f);
      shader_shadow.EndMode();
    light.EndMode();
  target.EndMode();

  // Draw to screen
  BeginDrawing();
    ClearBackground(GREEN);
    camera.BeginMode();
      shader_default.BeginMode();
        shader_default.SetValue(sd_shadow,target.depth);
        //TODO: shader_geom exclusively works for DrawMesh(). only use that function
      // shader_geom.BeginMode();
        // extra texture needs to be attached again for every draw call
        // shader_geom.SetValue(sg_shadow,target.depth);

        DrawCubeWiresV((Vector3){0.0f, 0.5f, 1.0f}, (Vector3){1.0f, 1.0f, 1.0f}, RED);
        DrawCubeV((Vector3){0.0f, 0.5f, 1.0f}, (Vector3){1.0f, 1.0f, 1.0f}, PURPLE);
        DrawCubeWiresV((Vector3){0.0f, 0.5f, -1.0f}, (Vector3){1.0f, 1.0f, 1.0f},
                        DARKGREEN);
        DrawCubeV((Vector3){0.0f, 0.5f, -1.0f}, (Vector3){1.0f, 1.0f, 1.0f}, YELLOW);
        DrawPlane(Vector3{0.0}, Vector2{5.0,5.0}, RED);
        DrawGrid(10, 1.0f);
      shader_default.EndMode();
      // shader_geom.EndMode();
    camera.EndMode();
    shader_depth.BeginMode();
      target.depth.Draw(screenDim*.95,0.0,-0.25f,WHITE);
    shader_depth.EndMode();
    DrawFPS(10, 10);
    DrawText((char*)rendererName, 10, 40, 5, RED);
  EndDrawing();
  //----------------------------------------------------------------------------------
}