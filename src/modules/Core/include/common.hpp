#pragma once

#ifdef PLATFORM_WEB
    #define GLSL_VERSION 100
#else
    #define GLSL_VERSION 330
#endif // PLATFORM_WEB

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define RESOURCE "resources" "/"
#define SHADER "resources/shaders/glsl" STR(GLSL_VERSION) "/"