#ifndef AQUAENGINE_GRAPHICS_SKYBOX_H
#define AQUAENGINE_GRAPHICS_SKYBOX_H

#include <graphics/Cubemap.h>
#include <graphics/Camera.h>
#include <graphics/Shader.h>
#include <graphics/Model.h>

class Skybox {
        Cubemap mSkybox;
        Shader mSkyboxShader;
        Model mSkyboxModel;
public:
        Skybox(std::vector<std::string> Faces, Shader& SkyboxShader, Model& SkyboxModel);

        void Draw(Camera& LocalCamera);
};

#endif
