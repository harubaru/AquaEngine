#include <graphics/Framebuffer.h>

Framebuffer::Framebuffer()
{
        glGenFramebuffers(1, &mFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);

        glGenRenderbuffers(1, &mRenderbuffer);

        glGenTextures(1, &mFramebufferData);
}

Framebuffer::~Framebuffer()
{
        glDeleteFramebuffers(1, &mFramebuffer);
}

void Framebuffer::Draw(int SrcX0, int SrcY0, int SrcX1, int SrcY1, int DstX0, int DstY0, int DstX1, int DstY1)
{
        glBlitFramebuffer(SrcX0, SrcY0, SrcX1, SrcY1, DstX0, DstY0, DstX1, DstY1, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void Framebuffer::Bind()
{
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, mFramebuffer);
}

void Framebuffer::Unbind()
{
        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

void Framebuffer::Begin()
{
        glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
}

void Framebuffer::End()
{
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLenum Framebuffer::GetFramebufferStatus()
{
        return glCheckFramebufferStatus(GL_FRAMEBUFFER);
}

void Framebuffer::AttachTexture(GLenum textarget)
{
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textarget, mFramebufferData, 0);
}

void Framebuffer::GenerateMultisample(int samples, int width, int height)
{
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, mFramebufferData);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB, width, height, false);
        AttachTexture(GL_TEXTURE_2D_MULTISAMPLE);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

        glBindRenderbuffer(GL_RENDERBUFFER, mRenderbuffer);
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRenderbuffer);
}
