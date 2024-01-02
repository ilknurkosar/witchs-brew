#include "RendererDefault.hpp"
#include "Camera3D.hpp"
#include "GLES2/gl2.h"
#include "Global.hpp"
#include "GuiCheckBox.hpp"
#include "GuiNode.hpp"
#include "Material.hpp"
#include "MaterialResource.hpp"
#include "MeshResource.hpp"
#include "NightGui.hpp"
#include "Node3D.hpp"
#include "RendererDefault.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "ShaderResource.hpp"
#include "SimpleModel3D.hpp"
#include "SimpleModelResource.hpp"
#include "VisualNode.hpp"
#include "common.hpp"
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "raylib-wrap.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

namespace raygui {
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
}

bool Global::showStats = true;
namespace
{
    // enum MYRESOURCES{
    //     SH_SHADOW,
    //     SH_DEPTH,
    //     SH_GEOM,
    //     SH_DEFAULT,
    //     MSH_CUBE,
    //     MT_DEFAULT,
    //     MSH_PLANE,
    //     SM_CUBE,
    //     SM_PLANE,
    // };
    // std::vector<std::unique_ptr<SimpleModel3D>> mysm;
    // std::vector<std::unique_ptr<GuiNode>> guis;
}

RendererDefault::RendererDefault(void)
    : screenDim({800, 450})
    //   target(screenDim.x, screenDim.y),
    //   resources()
{
//   resources.push_back(std::make_unique<ShaderResource>(LoadShader(SHADER "shadow.vs", SHADER "shadow.fs")));
//   resources.push_back(std::make_unique<ShaderResource>(LoadShader(0, SHADER "depth.fs")));
//   resources.push_back(std::make_unique<ShaderResource>(LoadShader(SHADER "geom.vs", SHADER "geom.fs")));
//   resources.push_back(std::make_unique<ShaderResource>(LoadShader(SHADER "default.vs", SHADER "default.fs")));
//   resources.push_back(std::make_unique<MeshResource>(GenMeshCube(1.0, 1.0, 1.0)));
//   // TODO: create material for shadows and stuff
//   resources.push_back(std::make_unique<MaterialResource>());
//   resources.push_back(std::make_unique<MeshResource>(GenMeshPlane(5.0, 5.0, 1, 1)));
//   resources.push_back(std::make_unique<SimpleModelResource>((MeshResource*)resources[MSH_CUBE].get(),(MaterialResource*)resources[MT_DEFAULT].get()));
//   resources.push_back(std::make_unique<SimpleModelResource>((MeshResource*)resources[MSH_PLANE].get(),(MaterialResource*)resources[MT_DEFAULT].get()));
//   //(Vector3){0.0f, 0.5f, 1.0f}, (Vector3){1.0f, 1.0f, 1.0f}
//   mysm.push_back(std::make_unique<SimpleModel3D>((SimpleModelResource*)resources[SM_CUBE].get(), PURPLE));
//   mysm[0]->t = MatrixTranslate(0.0f, 0.5f, 1.0f);
//   mysm.push_back(std::make_unique<SimpleModel3D>((SimpleModelResource*)resources[SM_CUBE].get(), YELLOW));
//   mysm[1]->t = MatrixTranslate(0.0f, 0.5f, -1.0f);
//   mysm.push_back(std::make_unique<SimpleModel3D>((SimpleModelResource*)resources[SM_PLANE].get(), GREEN));
//   guis.push_back(std::make_unique<GuiCheckBox>(Global::showStats,::Rectangle{10.0,70.0,20.0, 20.0}, "Show stats",[](bool x){Global::showStats = x;}));
//   guis.push_back(std::make_unique<NightGui>());
  rendererName = glGetString(GL_RENDERER);
}

static Matrix getNode2DTranfsorm(Node2D *n){
    Matrix out = n->t;
    for(Node* p = n->getParent(); p != Scene::getRoot(); p = p->getParent()){
        if(p->checkType(NodeType::NODE2D)){
            out = out * ((Node2D*)p)->t;
        }
    }
    return out;
}
static Matrix getNode3DTranfsorm(Node3D &n){
    Matrix out = n.t;
    for(Node* p = n.getParent(); p != nullptr; p = p->getParent()){
        if(p->checkType(NodeType::NODE3D))
            out = out * ((Node3D*)p)->t;
    }
    return out;
}

// Initializes 3D mode with custom camera (3D)
static void CustBeginMode3D(Camera cam,Matrix projection)
{
    BeginMode3D(cam);
    rlSetMatrixProjection(projection);
}

static void DrawGuis(std::vector<Node*> &v){
    for(auto g : v){
        GuiNode* temp = (GuiNode*)g;
        Matrix myt = getNode2DTranfsorm(temp);
        temp->display(myt);
    }
}

static void DrawSModel(SimpleModel3D &smodel){
/*
    // Material temp = smodel.getModel()->getMaterial().get();
    // temp.maps[MATERIAL_MAP_DIFFUSE].color
    raylib::Material& mat = smodel.getModel()->getMaterial().get();
    Color col = mat.maps[MATERIAL_MAP_DIFFUSE].color;
    Shader shad = mat.shader;
    mat.maps[MATERIAL_MAP_DIFFUSE].color = smodel.getColor();
    mat.shader = activeShader;
    mat.DrawMesh(smodel.getModel()->getMesh().get(), getNode3DTranfsorm(smodel));
    mat.maps[MATERIAL_MAP_DIFFUSE].color = col;
    mat.shader = shad;
*/
    ::DrawMesh(smodel.getModel()->getMesh().get(),smodel.getModel()->getMaterial().get(), getNode3DTranfsorm(smodel));
}
static void DrawSModels(std::vector<std::unique_ptr<SimpleModel3D>> &v){
    for(auto &sm : v)
        DrawSModel(*sm.get());
}

void RendererDefault::process(double delta) {

//   static raylib::Camera camera{
//       Vector3{0.5f, 1.0f, 1.5f}, // Camera position
//       Vector3{0.0f, 0.5f, 0.0f}, // Camera looking at point
//       Vector3{0.0f, 1.0f, 0.0f}, // Camera up vector (rotation towards target)
//       45.0f,                     // Camera field-of-view Y
//       CAMERA_PERSPECTIVE         // Camera projection type
//   };

  std::vector<Node*> visibles = Scene::getVisual();
  std::vector<Node*> guis{};
  std::copy_if(visibles.begin(),visibles.end(),std::back_inserter(guis),[](Node* x)->bool{return x->checkType(NodeType::GUI);});


/* //TODO cry
  static raylib::Shader &shader_shadow = ((ShaderResource*)(resources[SH_SHADOW].get()))->getShader();
  static raylib::Shader &shader_depth = ((ShaderResource*)(resources[SH_DEPTH].get()))->getShader();
  static raylib::Shader &shader_geom= ((ShaderResource*)(resources[SH_GEOM].get()))->getShader();
  static raylib::Shader &shader_default= ((ShaderResource*)(resources[SH_DEFAULT].get()))->getShader();

  static raylib::Camera light{
      Vector3{5.0f, 2.0f, 5.0f}, // Camera position
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

  static int sd_shadow = shader_default.GetLocation("texture1");
  static int sd_ivp = shader_default.GetLocation("ivp");
  static int sd_lightMat = shader_default.GetLocation("lightMat");

  // Update
  //----------------------------------------------------------------------------------
//   camera.Update(CAMERA_FIRST_PERSON);
//   light.Update(CAMERA_ORBITAL);

  Matrix lightPMat = MatrixPerspective(light.fovy * DEG2RAD,
                        double(screenDim.x) / double(screenDim.y),
                        1.0, 40.0);
  Matrix lightMat = lightPMat * light.GetMatrix();
  Matrix ivp =
      Invert(MatrixPerspective(camera.fovy * DEG2RAD,
                               double(screenDim.x) / double(screenDim.y),
                               RL_CULL_DISTANCE_NEAR, RL_CULL_DISTANCE_FAR) *
             camera.GetMatrix());
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
  CustBeginMode3D(light, lightPMat);
    DrawSModels(mysm,shader_shadow);
  light.EndMode();
  target.EndMode();

*/
  // Draw to screen
  BeginDrawing();
  ClearBackground(GREEN);
//   camera.BeginMode();
//   shader_default.BeginMode();
//   shader_default.SetValue(sd_shadow, target.depth);
  // TODO: shader_geom exclusively works for DrawMesh(). only use that function
  // shader_geom.BeginMode();
  // extra texture needs to be attached again for every draw call
  // shader_geom.SetValue(sg_shadow,target.depth);

    // DrawSModels(mysm);
//   shader_default.EndMode();
  // shader_geom.EndMode();
//   camera.EndMode();
//   shader_depth.BeginMode();
//   target.depth.Draw(screenDim * .95, 0.0, -0.25f, WHITE);
//   shader_depth.EndMode();

    DrawGuis(guis);
    // ((GuiNode*)(guis.front()))->display(MatrixIdentity());

  if(Global::showStats){
    DrawFPS(10, 10);
    DrawText((char *)rendererName, 10, 40, 5, RED);
  }
  EndDrawing();
  //----------------------------------------------------------------------------------
}