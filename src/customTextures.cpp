#include "customTextures.hpp"
#include "raylib.h"
#include "rlgl.h"
#include <charconv>
#include <cstdio>
#include <stdexcept>
#include <string>

namespace raylib {
    // SHADOW TEXTURE ======================================================
    ShadowTexture::ShadowTexture(int width, int height){
        this->id = rlLoadFramebuffer(width, height);
        this->width = width;
        this->height = height;

        if(this->id > 0){
            rlEnableFramebuffer(this->id);

            this->depth.id = rlLoadTextureDepth(width, height, false);
            this->depth.width = width;
            this->depth.height = height;
            this->depth.format = 19;
            this->depth.mipmaps = 1;
            if(this->depth.id <= 0)
                TRACELOG(LOG_WARNING,"Depth Texture for Shadowmap[%i] returned invalid code(%i)",this->id,this->depth.id);

            rlTextureParameters(this->depth.id, RL_TEXTURE_WRAP_S, RL_TEXTURE_WRAP_CLAMP);
            rlTextureParameters(this->depth.id, RL_TEXTURE_WRAP_T, RL_TEXTURE_WRAP_CLAMP);
            rlFramebufferAttach(this->id, this->depth.id, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_TEXTURE2D, 0);

            if (rlFramebufferComplete(this->id)) TraceLog(LOG_INFO, "FBO: [ID %i] Shadow Framebuffer object created successfully", this->id);
            else TraceLog(LOG_WARNING, "FBO: [ID %i] Shadow Framebuffer object creation failed.", this->id);

            rlDisableFramebuffer();
        }else TraceLog(LOG_WARNING, "FBO: Shadow Framebuffer object can not be created");
    }
    ShadowTexture::~ShadowTexture(){
        rlUnloadFramebuffer(this->id);
        rlUnloadTexture(this->depth.id);
    }

    void ShadowTexture::BeginMode(){
        BeginTextureMode(
            ::RenderTexture2D{
            .id=this->id,
            .texture=depth,
            .depth=depth
        });
    }

    void ShadowTexture::EndMode(){
        EndTextureMode();
    }
    // WRITABLE DEPTH TEXTURE ======================================================
    WritableDepthTexture::WritableDepthTexture(int width, int height){
        this->id = rlLoadFramebuffer(width, height);   // Load an empty framebuffer
        if (this->id > 0)
        {
            rlEnableFramebuffer(this->id);

            // Create color texture (default to RGBA)
            this->texture.id = rlLoadTexture(0, width, height, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);
            this->texture.width = width;
            this->texture.height = height;
            this->texture.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
            this->texture.mipmaps = 1;

            // Create depth texture buffer (instead of raylib default renderbuffer)
            this->depth.id = rlLoadTextureDepth(width, height, false);
            this->depth.width = width;
            this->depth.height = height;
            this->depth.format = 19;       //DEPTH_COMPONENT_24BIT?
            this->depth.mipmaps = 1;

            // Attach color texture and depth texture to FBO
            rlFramebufferAttach(this->id, this->texture.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_TEXTURE2D, 0);
            rlFramebufferAttach(this->id, this->depth.id, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_TEXTURE2D, 0);

            // Check if fbo is complete with attachments (valid)
            if (rlFramebufferComplete(this->id)) TRACELOG(LOG_INFO, "FBO: [ID %i] Framebuffer object created successfully", this->id);

            rlDisableFramebuffer();
        }
        else TRACELOG(LOG_WARNING, "FBO: Framebuffer object can not be created");
    }
    WritableDepthTexture::~WritableDepthTexture(){
        if (this->id > 0)
        {
            // Color texture attached to FBO is deleted
            rlUnloadTexture(this->texture.id);
            rlUnloadTexture(this->depth.id);

            // NOTE: Depth texture is automatically
            // queried and deleted before deleting framebuffer
            rlUnloadFramebuffer(this->id);
        }
    }
    void WritableDepthTexture::BeginMode(){
        ::BeginTextureMode(*this);
    }
    void WritableDepthTexture::EndMode(){
        ::EndTextureMode();
    }
}