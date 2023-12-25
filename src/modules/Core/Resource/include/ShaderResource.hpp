#pragma once

#include "Resource.hpp"
#include "ResourceType.hpp"
#include "Shader.hpp"
#include "raylib.h"

class ShaderResource : virtual private ResourceType, public Resource {
protected:
  raylib::Shader _shader;
public:
  inline raylib::Shader& getShader(){return _shader;}
  explicit ShaderResource() = delete;
  explicit inline ShaderResource(::Shader shader) : _shader(shader){this->f |= ResourceType::SHADER;}
  explicit ShaderResource(const ShaderResource &) = delete;
  explicit ShaderResource(ShaderResource &&) = delete;
  ShaderResource &operator=(ShaderResource &&) = default;
  ShaderResource &operator=(const ShaderResource &) = delete;
  virtual ~ShaderResource();
};
