#ifndef AQUAGL_FRAMEBUFFER_H
#define AQUAGL_FRAMEBUFFER_H

#include <iostream>
#include <GL/glew.h>

class Framebuffer {
        GLuint mFramebuffer;
        GLuint mFramebufferTex;
        GLuint mRenderbuffer;
public:
        Framebuffer(unsigned int width, unsigned int height);
        ~Framebuffer();

        void Bind();
        void Unbind();
        void BindTex();
        void UnbindTex();
};

#endif
