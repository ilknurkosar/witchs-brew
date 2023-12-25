#pragma once

#include "Resource.hpp"
#include "ResourceType.hpp"
#include "Texture.hpp"
#include "raylib.h"

class TextureResource : virtual private ResourceType, public Resource {
protected:
  raylib::Texture _texture;
public:
  inline raylib::Texture& getTexture(){return _texture;}
  explicit TextureResource() = delete;
  explicit inline TextureResource(::Texture texture) : _texture(texture){this->f |= ResourceType::TEXTURE;}
  explicit TextureResource(const TextureResource &) = delete;
  explicit TextureResource(TextureResource &&) = delete;
  TextureResource &operator=(TextureResource &&) = default;
  TextureResource &operator=(const TextureResource &) = delete;
  virtual ~TextureResource() = default;
};