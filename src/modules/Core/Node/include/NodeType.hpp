#pragma once

#include <cstdint>
class NodeType {
protected:
  uint32_t f = 0; // this variable is not visible to the end-user

public:
  enum FLAG {
    PROCESSABLE = 1 << 0,
    VISUAL = 1 << 1,
    NODE2D = 1 << 2,
    NODE3D = 1 << 3,
    MODEL3D = 1 << 4,
    CAMERA3D = 1 << 5,
    TEXTURE2D = 1 << 6,
    TEXT2D = 1 << 7,
    TEXT3D = 1 << 8,
  };
  explicit NodeType() = default;
};