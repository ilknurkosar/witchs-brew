#pragma once

#include "Ray.hpp"
#include "RenderTexture.hpp"
#include "Texture.hpp"
#include "raylib.h"

namespace raylib {
    //based on GoldenThumbs/raylibShadowmap
    class ShadowTexture{
      public: //attributes
        unsigned int id;
        int width;
        int height;
        raylib::Texture2D depth;
      public: //methods
        ShadowTexture(int width, int height);
        ~ShadowTexture();
        void BeginMode();
        void EndMode();
    };
    class WritableDepthTexture: public ::RenderTexture{
      public: //attributes
      public: //methods
        WritableDepthTexture(int width, int height);
        ~WritableDepthTexture();
        void BeginMode();
        void EndMode();
    };
}