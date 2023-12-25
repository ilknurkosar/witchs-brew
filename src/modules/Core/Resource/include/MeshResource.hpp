#pragma once

#include "Resource.hpp"
#include "ResourceType.hpp"
#include "Mesh.hpp"
#include "raylib.h"

class MeshResource : virtual private ResourceType, public Resource {
protected:
  raylib::Mesh _mesh;
public:
  inline raylib::Mesh& getMesh(){return _mesh;}
  explicit MeshResource() = delete;
  explicit inline MeshResource(::Mesh mesh) : _mesh(mesh){this->f |= ResourceType::MESH;}
  explicit MeshResource(const MeshResource &) = delete;
  explicit MeshResource(MeshResource &&) = delete;
  MeshResource &operator=(MeshResource &&) = default;
  MeshResource &operator=(const MeshResource &) = delete;
  virtual ~MeshResource();
};