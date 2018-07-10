#ifndef AQUAENGINE_GRAPHICS_FRAMEBUFFER_H
#define AQUAENGINE_GRAPHICS_FRAMEBUFFER_H

#include <export.h>

#include <iostream>
#include <vector>
#include <graphics/gl3w.h>
#include <graphics/Mesh.h>
#include <graphics/Shader.h>

class API Framebuffer {
        GLuint mFramebuffer;
        GLuint mFramebufferTex;
        GLuint mRenderbuffer;

        void BindTex();
        void UnbindTex();

        Vertex FBQuadVertices[4] = {
		Vertex(1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0),
		Vertex(1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0),
		Vertex(-1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0),
		Vertex(-1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0)
	};

	std::vector<uint32_t> FBQuadIndices = {
		0, 1, 3,
		1, 2, 3
	};

        Shader FBShader;
	Mesh FBQuad;
public:
        Framebuffer() {}
        Framebuffer(unsigned int width, unsigned int height, Shader &shader);
        ~Framebuffer();

        void Load(unsigned int width, unsigned int height, Shader &shader);
        void Destroy();
        void Resize(unsigned int width, unsigned int height);

        void Bind();
        void Unbind();

        void Draw();
};

#endif
