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
  inline raylib::Material& get() {return _material;}
  explicit inline MaterialResource(): _material() {this->f |= ResourceType::MATERIAL;};
  explicit inline MaterialResource(::Material material): _material(material){this->f |= ResourceType::MATERIAL;}
  explicit inline MaterialResource(ShaderResource& shader)
  : MaterialResource()
  {
    _material.SetShader(shader.getShader());
  }
  explicit inline MaterialResource(ShaderResource& shader, TextureResource& texture)
  : MaterialResource(shader)
  {
    ::UnloadTexture(_material.maps[MATERIAL_MAP_DIFFUSE].texture);
    _material.SetTexture(MATERIAL_MAP_DIFFUSE,texture.getTexture());
  }
  explicit MaterialResource(const MaterialResource &) = delete;
  explicit MaterialResource(MaterialResource &&) = delete;
  MaterialResource &operator=(MaterialResource &&) = default;
  MaterialResource &operator=(const MaterialResource &) = delete;
  virtual ~MaterialResource() = default;
};
