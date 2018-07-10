#ifndef AQUAENGINE_GRAPHICS_SKYBOX_H
#define AQUAENGINE_GRAPHICS_SKYBOX_H

#include <export.h>

#include <iostream>
#include <graphics/Cubemap.h>
#include <graphics/Camera.h>
#include <graphics/Shader.h>

class API Skybox {
        Cubemap mSkybox;
        Shader mSkyboxShader;
public:
        Skybox(std::string filepath, std::string extension);
        ~Skybox();

        void Destroy();
        void Draw(Camera& LocalCamera);
};

#endif
