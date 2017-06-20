#ifndef AQUAGL_FRAMEBUFFER_H
#define AQUAGL_FRAMEBUFFER_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <graphics/Mesh.h>
#include <graphics/Shader.h>

class Framebuffer {
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
        Framebuffer(unsigned int width, unsigned int height);
        ~Framebuffer();

        void Bind();
        void Unbind();

        void Draw();
};

#endif
