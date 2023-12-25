#pragma once

#include "Material.hpp"
#include "Resource.hpp"
#include "ResourceType.hpp"
#include "Shader.hpp"
#include "ShaderResource.hpp"
#include "TextureResource.hpp"
#include "raylib.h"

class MaterialResource : virtual private ResourceType, public Resource {
protected:
  raylib::Material _material;
public:
  inline raylib::Material& getMaterial(){return _material;}
  explicit MaterialResource() = delete;
  explicit inline MaterialResource(ShaderResource& shader, TextureResource& texture)
  : _material()
  {
    this->f |= ResourceType::MATERIAL;
    ::UnloadTexture(_material.maps[MATERIAL_MAP_DIFFUSE].texture);
    _material.SetTexture(MATERIAL_MAP_DIFFUSE,texture.getTexture());
    _material.SetShader(shader.getShader());
  }
  explicit MaterialResource(const MaterialResource &) = delete;
  explicit MaterialResource(MaterialResource &&) = delete;
  MaterialResource &operator=(MaterialResource &&) = default;
  MaterialResource &operator=(const MaterialResource &) = delete;
  virtual ~MaterialResource() = default;
};
