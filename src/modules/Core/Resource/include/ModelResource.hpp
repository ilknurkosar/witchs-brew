#pragma once

#include "Model.hpp"
#include "Resource.hpp"
#include "ResourceType.hpp"
#include "raylib.h"

class ModelResource : virtual private ResourceType, public Resource {
protected:
  raylib::Model _model;
public:
  inline raylib::Model& getModel(){return _model;}
  explicit ModelResource() = delete;
  explicit inline ModelResource(::Model model)
  : _model(model)
  {
    this->f |= ResourceType::MODEL;
  }
  explicit ModelResource(const ModelResource &) = delete;
  explicit ModelResource(ModelResource &&) = delete;
  ModelResource &operator=(ModelResource &&) = default;
  ModelResource &operator=(const ModelResource &) = delete;
  virtual ~ModelResource() = default;
};
