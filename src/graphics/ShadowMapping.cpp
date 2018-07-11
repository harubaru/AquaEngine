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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, ConVar_GetFloat("mat_ShadowResolution"), ConVar_GetFloat("mat_ShadowResolution"), 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
//	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);

	float border[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border); 

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_texture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "ShadowMapping Error: Framebuffer is not complete." << std::endl;

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowMapping_RenderDirectionalShadow(glm::vec3 light_pos, glm::vec3 light_dir, Shader &shader)
{
	glm::vec3 position = light_pos;
	glm::vec3 target = position + light_dir;
	glm::mat4 projection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 1.0f, 200.0f);
	glm::mat4 view = glm::lookAt(target, position, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 LightSpaceMatrix = projection * view;

	FBShader.SetMat4("LightSpaceMatrix", LightSpaceMatrix);
	FBShader.Unbind();

	shader.Bind();
	shader.SetMat4("LightSpaceMatrix", LightSpaceMatrix);
	shader.SetVec3("DirectionalLight.Direction", light_dir);
	shader.SetVec3("DirectionalLight.Position", light_pos);
	shader.SetInt("shadowFiltering", ConVar_GetFloat("mat_ShadowFiltering"));
	shader.SetInt("shadowsEnabled", 1);
	shader.Unbind();

	FBShader.Bind();

	glViewport(0, 0, ConVar_GetFloat("mat_ShadowResolution"), ConVar_GetFloat("mat_ShadowResolution"));
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glClear(GL_DEPTH_BUFFER_BIT);

//	glCullFace(GL_FRONT);
}

void ShadowMapping_RenderReset(int w, int h)
{
	glViewport(0, 0, w, h);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glCullFace(GL_BACK);
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
