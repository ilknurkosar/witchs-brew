#pragma once

#include <cstdint>
class ResourceType {
protected:
  uint32_t f = 0; // this variable is not visible to the end-user

public:
  enum FLAG {
    SHADER = 1 << 0,
    FONT = 1 << 1,
    TEXTURE = 1 << 2,
    MESH = 1 << 3,
    MATERIAL = 1 << 4,
  };
  explicit ResourceType() = default;
};