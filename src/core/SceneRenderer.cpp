#include <core/SceneRenderer.h>

/*

Shader 0 = Shader for rendering regular objects
Shader 1 = Shader for capturing depth buffer *requires one pass*

*/

#define MESH_SHADER 0
#define DEPTH_SHADER 1
#define POSTPROCESS_SHADER 2

std::vector<std::string> shader_paths = {
	"./resources/shaders/primitives/mesh",
	"./resources/shaders/framebuffer/sm",
	"./resources/shaders/framebuffer/pp"
};

SceneRenderer::SceneRenderer(int w, int h)
{
	// Initialize Shaders
	for (size_t i = 0; i < shader_paths.size(); i++)
		this->shaders[i].Load(shader_paths[i]);

	ShadowMapping_Init(this->shaders[DEPTH_SHADER]);
	fb.Load(w, h, this->shaders[POSTPROCESS_SHADER]);
}

void SceneRenderer::Add(PhysEntity &ent)
{
	this->renderlist.push_back(ent);
}

void SceneRenderer::Remove(PhysEntity &ent)
{
	for (unsigned int i = 0; i < this->renderlist.size(); i++) {
		if (this->renderlist.at(i) == ent)
			this->renderlist.erase(this->renderlist.begin() + i);
	}
}

void SceneRenderer::Update(Display &display, Camera &camera)
{
	// Pass 1 - Capturing Depth Buffer for rendering shadows
	this->shaders[DEPTH_SHADER].Bind();

	ShadowMapping_RenderDirectionalShadow(glm::vec3(0.0f, 5.0f, -2.0f), this->shaders[MESH_SHADER]);

	this->shaders[DEPTH_SHADER].SetProjection(camera.GetProjection());
	this->shaders[DEPTH_SHADER].SetView(camera.GetView());
	this->shaders[DEPTH_SHADER].SetVec3("viewPos", camera.GetPos());

	for (auto &i : this->renderlist)
		i.Render(this->shaders[DEPTH_SHADER]);

	int Width, Height;
	display.GetSize(&Width, &Height);
	ShadowMapping_RenderReset(Width, Height);

	// Pass 2 - Actually rendering objects

	this->fb.Bind();

	this->shaders[MESH_SHADER].Bind();

	this->shaders[MESH_SHADER].SetProjection(camera.GetProjection());
	this->shaders[MESH_SHADER].SetView(camera.GetView());
	this->shaders[MESH_SHADER].SetVec3("viewPos", camera.GetPos());

	for (auto &i : this->renderlist)
		i.Render(this->shaders[MESH_SHADER]);

	this->shaders[MESH_SHADER].Unbind();

	// Do post-processing
	this->fb.Unbind();
	this->fb.Draw();
}
