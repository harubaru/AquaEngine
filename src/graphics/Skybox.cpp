#include <graphics/Skybox.h>

Skybox::Skybox(std::vector<std::string> Faces, Shader& SkyboxShader, Model& SkyboxModel)
{
        mSkybox.Load(Faces);
        mSkyboxShader = SkyboxShader;
        mSkyboxModel = SkyboxModel;
}

void Skybox::Draw(Camera& LocalCamera)
{
        glDepthFunc(GL_LEQUAL);

        mSkyboxShader.Bind();
        mSkyboxShader.SetProjection(LocalCamera.GetProjection());
        mSkyboxShader.SetView(glm::mat4(glm::mat3(LocalCamera.GetView())));

        mSkybox.Bind();
        mSkyboxModel.Render();
        mSkybox.Unbind();

        mSkyboxShader.Unbind();

        glDepthFunc(GL_LESS);
}
