#pragma once

#include <cstdint>
class NodeType {
private:
  uint32_t f = 0; // this variable is not visible to the end-user
public:
  enum FLAG {
    PROCESSABLE = 1 << 0,
    VISUAL = 1 << 1,
    NODE2D = 1 << 2,
    NODE3D = 1 << 3,
    MODEL3D = 1 << 4,
    SIMPLEMODEL3D = 1 << 5,
    CAMERA3D = 1 << 6,
    TEXTURE2D = 1 << 7,
    TEXT2D = 1 << 8,
    TEXT3D = 1 << 9,
    GUI = 1 << 10,
  };
  inline bool checkType(NodeType::FLAG f){return this->f & f;}
  explicit NodeType() = default;
  virtual ~NodeType() = default;
protected:
  inline void setFlag(NodeType::FLAG f){this->f |= f;}
};