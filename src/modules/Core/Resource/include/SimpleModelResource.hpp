#pragma once

#include "MaterialResource.hpp"
#include "MeshResource.hpp"
#include "Model.hpp"
#include "Resource.hpp"
#include "ResourceType.hpp"
#include "raylib.h"

class SimpleModelResource : virtual private ResourceType, public Resource {
protected:
  MeshResource const *_mesh;
  MaterialResource const *_material;
public:
  inline MeshResource const& getMesh(){return *_mesh;}
  inline MaterialResource const& getMaterial(){return *_material;}
  explicit SimpleModelResource() = delete;
  explicit inline SimpleModelResource(MeshResource *mesh, MaterialResource *material)
  : _material(material),
  _mesh(mesh)
  {
    this->f |= ResourceType::SIMPLEMODEL;
  }
  explicit SimpleModelResource(const SimpleModelResource &) = delete;
  explicit SimpleModelResource(SimpleModelResource &&) = delete;
  SimpleModelResource &operator=(SimpleModelResource &&) = default;
  SimpleModelResource &operator=(const SimpleModelResource &) = delete;
  virtual ~SimpleModelResource() = default;
};
