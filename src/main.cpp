
#include <pthread.h>

#include <util/Clock.h>
#include <graphics/Graphics.h>
#include <graphics/Camera.h>
#include <graphics/Skybox.h>
#include <graphics/TextRenderer.h>
#include <graphics/ShadowMapping.h>
#include <graphics/Map.h>
#include <core/SceneObject.h>
#include <core/Input.h>
#include <core/SceneRenderer.h>
#include <core/ConVar.h>
#include <core/Debug.h>
#include <AL/alc.h>
#include <audio/ogg.h>

#include <core/BSPParser.h>

void *audiothread(void *args)
{
	ALCcontext *context;
	ALCdevice *device;

	device = alcOpenDevice(alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER));
	if (!device) {
		LOG("Unable to create OpenAL device!");
	}

	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);

	ogg music1("./resources/sound/music/dreams.ogg");

	while (true)
		music1.Play();

	return args;
}

int main()
{
	Debug_Init("log.txt");
	ConVar_LoadFile("./resources/cfg/display.cfg");
	ConVar_LoadFile("./resources/cfg/graphics.cfg");

	float width = ConVar_GetFloat("width");
	float height = ConVar_GetFloat("height");

	Display display(width, height, ConVar_GetString("title"), 0);
	Graphics graphics(display);	

	Clock clock;
	Clock_Initialize(&clock);

	Camera camera(glm::vec3(4, 5, 0), ConVar_GetFloat("cl_fov"), (float)width / (float)height, ConVar_GetFloat("cl_near"), ConVar_GetFloat("cl_far"));
	camera.LockCursor();

	BSPParser bsp(std::string("./resources/maps/maptest.bsp"));
	Map map(&bsp);

	Skybox skybox("./resources/textures/skybox/browncloud", "jpg");

	SceneObject cube("./resources/meshes/Cube.obj", "./resources/textures/WoodPlanksDiffuseMap.jpg", vec3(0, 9, 0), vec3(0, 1, 0), vec3(6));
	SceneObject dude("./resources/meshes/nanosuit.obj", "./resources/textures/smoothmetal.jpg", vec3(0, 1, 0), vec3(0, 1, 0), vec3(1));

	TextRenderer textmgr(ConVar_GetFloat("width"), ConVar_GetFloat("height"));
	textmgr.LoadFont("./resources/fonts/FreeSans.ttf", 15);
	SceneRenderer scenemgr;

	scenemgr.AddObject(cube);
	scenemgr.AddObject(dude);
	scenemgr.AddSkybox(skybox);
	scenemgr.AddMap(map);

	double delta = 0;

	pthread_t audio_thread;
	pthread_create(&audio_thread, NULL, audiothread, NULL);

	while(!display.m_Input.m_WindowClose) {
		Clock_TickBegin(&clock);
		float radius = 12.0f;
		delta += clock.DeltaTime * 2;
		float x = sin(delta) * radius;
		float z = cos(delta) * radius;
		graphics.GetGLError();
//		graphics.Clear(); this is disabled because we're drawing a skybox
		
		x += 1 * clock.DeltaTime;
		dude.Transform.SetPos(glm::vec3(x, 5 , z));
		scenemgr.Update(display, camera);
		textmgr.RenderText("AquaEngine - FPS: " + std::to_string(1.0 / clock.DeltaTime), 15, ConVar_GetFloat("height") - 20, 1, glm::vec3(1, 1, 1));
		display.Update();

		camera.Update(display, display.m_Input, clock.DeltaTime, true, ConVar_GetFloat("cl_fov"), (float)width / (float)height, ConVar_GetFloat("cl_near"), ConVar_GetFloat("cl_far"));
		Clock_TickEnd(&clock);
		display.LimitRefreshRate(&clock.DeltaTime);
	}

	pthread_cancel(audio_thread);
	Debug_Kill();

	return 0;
}
