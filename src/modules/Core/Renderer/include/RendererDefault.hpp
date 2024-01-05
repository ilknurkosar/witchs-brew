#pragma once

#include "GLES2/gl2.h"
#include "Node.hpp"
#include "Renderer.hpp"
#include "Resource.hpp"
#include "Shader.hpp"
#include "customTextures.hpp"
#include <memory>
#include <vector>

class RendererDefault :public Renderer {
public: // Attributes
  Vector2 screenDim;
private:
  raylib::ShadowTexture target;
  const GLubyte *rendererName;
  std::vector<Node*> visibles;

public: // Methods
  static void fetchVisibles();
  void process() override;
  RendererDefault();
  ~RendererDefault() = default;
private:
};