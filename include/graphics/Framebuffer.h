#ifndef AQUAGL_FRAMEBUFFER_H
#define AQUAGL_FRAMEBUFFER_H

#include <GL/glew.h>

class Framebuffer {
        GLuint mFramebuffer;
        GLuint mFramebufferData;
        GLuint mRenderbuffer;
public:
        Framebuffer();
        ~Framebuffer();

        void Draw(int SrcX0, int SrcY0, int SrcX1, int SrcY1, int DstX0, int DstY0, int DstX1, int DstY1);
        void Bind();
        void Unbind();
        void Begin();
        void End();
        void AttachTexture(GLenum textarget);
        void GenerateMultisample(int samples, int width, int height);
        GLenum GetFramebufferStatus();
};

#endif
