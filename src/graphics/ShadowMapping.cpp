#include <graphics/ShadowMapping.h>

static GLuint fbo = 0;
static GLuint depth_texture = 0;

Shader FBShader;

void ShadowMapping_Init(Shader &shader)
{
	FBShader = shader;

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &depth_texture);
	glBindTexture(GL_TEXTURE_2D, depth_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_texture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "ShadowMapping Error: Framebuffer is not complete." << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowMapping_RenderDirectionalShadow(glm::vec3 light_pos, Shader &shader)
{
	glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 10.0f);
	glm::mat4 view = glm::lookAt(light_pos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 LightSpaceMatrix = projection * view;

	FBShader.SetMat4("LightSpaceMatrix", LightSpaceMatrix);
	FBShader.Unbind();

	shader.Bind();
	shader.SetMat4("LightSpaceMatrix", LightSpaceMatrix);
	shader.SetVec3("lightPos", light_pos);
	shader.Unbind();

	FBShader.Bind();

	glViewport(0, 0, 1024, 1024);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void ShadowMapping_RenderReset(int w, int h)
{
	glViewport(0, 0, w, h);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ShadowMapping_Bind(void)
{
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depth_texture);
}

void ShadowMapping_Unbind(void)
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
