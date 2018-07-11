#include <core/SceneRenderer.h>

#define MESH_SHADER 0
#define DEPTH_SHADER 1
#define POSTPROCESS_SHADER 2
#define WIREFRAME_SHADER 3

std::vector<std::string> shader_paths = {
	"./resources/shaders/primitives/mesh",
	"./resources/shaders/framebuffer/sm",
	"./resources/shaders/framebuffer/pp",
	"./resources/shaders/primitives/wireframe"
};

void SceneRenderer::Load()
{
	for (size_t i = 0; i < shader_paths.size(); i++)
		this->shaders[i].Load(shader_paths[i]);

	ShadowMapping_Init(this->shaders[DEPTH_SHADER]);
	fb.Load(ConVar_GetFloat("width"), ConVar_GetFloat("height"), this->shaders[POSTPROCESS_SHADER]);

	this->shaders[MESH_SHADER].Bind();
	this->shaders[MESH_SHADER].SetInt("diffuseTexture", 0);
	this->shaders[MESH_SHADER].SetInt("shadowMap", 1);
	this->shaders[MESH_SHADER].Unbind();

	this->skybox = nullptr;
}

void SceneRenderer::AddObject(SceneObject &object)
{
	this->renderlist.push_back(object);
}

void SceneRenderer::RemoveObject(SceneObject &object)
{
	for (unsigned int i = 0; i < this->renderlist.size(); i++) {
		if (this->renderlist.at(i) == object)
			this->renderlist.erase(this->renderlist.begin() + i);
	}
}

void SceneRenderer::AddSkybox(Skybox &skybox)
{
	this->skybox = &skybox;
}

void SceneRenderer::Update(Display &display, Camera &camera)
{
	
	if (ConVar_GetFloat("mat_Shadows")) {
		this->shaders[DEPTH_SHADER].Bind();

		ShadowMapping_RenderDirectionalShadow(camera.GetPos(), vec3(0, 20, 20), this->shaders[MESH_SHADER]);

		for (auto &i : this->renderlist)
			i.Render(this->shaders[DEPTH_SHADER]);

		ShadowMapping_RenderReset(ConVar_GetFloat("width"), ConVar_GetFloat("height"));
		this->shaders[DEPTH_SHADER].Unbind();
	} else {
		this->shaders[MESH_SHADER].Bind();
		this->shaders[MESH_SHADER].SetInt("shadowsEnabled", 0);
		this->shaders[MESH_SHADER].Unbind();
	}

	this->fb.Bind();

	this->shaders[MESH_SHADER].Bind();

	this->shaders[MESH_SHADER].SetProjection(camera.GetProjection());
	this->shaders[MESH_SHADER].SetView(camera.GetView());
	this->shaders[MESH_SHADER].SetVec3("viewPos", camera.GetPos());

	this->shaders[MESH_SHADER].SetInt("mat_fullbright", static_cast<int>(ConVar_GetFloat("mat_fullbright")));

	for (auto &i : this->renderlist)
		i.Render(this->shaders[MESH_SHADER]);

	this->shaders[MESH_SHADER].Unbind();

	if (skybox) {
		if (ConVar_GetFloat("r_skybox")) {
			this->skybox->Draw(camera);
			LOG("skybox!\n");
		}
	}

	this->fb.Unbind();
	this->fb.Draw();
}
