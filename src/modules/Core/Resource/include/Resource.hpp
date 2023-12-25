#pragma once

#include "ResourceType.hpp"

class Resource : virtual private ResourceType {
protected:
public:
  inline bool checkType(ResourceType::FLAG f) { return this->f & f; }
  explicit Resource() = default;
  explicit Resource(const Resource &) = delete;
  explicit Resource(Resource &&) = delete;
  Resource &operator=(Resource &&) = default;
  Resource &operator=(const Resource &) = default;
  virtual ~Resource() = default;
};