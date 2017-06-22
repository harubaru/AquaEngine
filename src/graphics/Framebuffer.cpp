#include <graphics/Framebuffer.h>

Framebuffer::Framebuffer(unsigned int width, unsigned int height)
{
        // Generate Framebuffer
        glGenFramebuffers(1, &mFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);

        // Generate Tex Attachment
        glGenTextures(1, &mFramebufferTex);
        glBindTexture(GL_TEXTURE_2D, mFramebufferTex);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mFramebufferTex, 0);

        glGenRenderbuffers(1, &mRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, mRenderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRenderbuffer);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "Framebuffer Error: Framebuffer is not complete." << std::endl;

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        FBShader.Load("resources/shaders/framebuffer/vert_fb.glsl", "resources/shaders/framebuffer/frag_fb.glsl");
        FBQuad.Load(FBQuadVertices, FBQuadIndices, FBQuadIndices.size());

        FBShader.Bind();
        FBShader.SetInt("tex", 0);
        FBShader.Unbind();
}

Framebuffer::~Framebuffer()
{
        glDeleteTextures(1, &mFramebufferTex);
        glDeleteRenderbuffers(1, &mRenderbuffer);
        glDeleteFramebuffers(1, &mFramebuffer);
}

void Framebuffer::Bind()
{
        glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
}

void Framebuffer::Unbind()
{
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::BindTex()
{
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mFramebufferTex);
}

void Framebuffer::UnbindTex()
{
        glBindTexture(GL_TEXTURE_2D, 0);
}

void Framebuffer::Draw()
{
        glDisable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT);
        FBShader.Bind();
        BindTex();
        FBQuad.Draw();
        UnbindTex();
        FBShader.Unbind();
        glEnable(GL_DEPTH_TEST);
}
