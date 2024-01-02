#pragma once

#include "GLES2/gl2.h"
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
  // raylib::ShadowTexture target;
  const GLubyte *rendererName;

public: // Methods
  void process(double delta) override;
  RendererDefault();
  ~RendererDefault() = default;
private:
};