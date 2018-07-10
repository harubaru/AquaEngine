#include <graphics/Cubemap.h>

Cubemap::Cubemap(std::vector<std::string> Faces)
{
        Load(Faces);
}

Cubemap::~Cubemap()
{
        glDeleteTextures(1, &mTex);
}

#include <iostream>

void Cubemap::Load(std::vector<std::string> Faces)
{
        glGenTextures(1, &mTex);
        glBindTexture(GL_TEXTURE_CUBE_MAP, mTex);

        int width, height, comp;
        for(uint32_t i = 0; i < 6; i++) {
                unsigned char* TexData = stbi_load(Faces[i].c_str(), &width, &height, &comp, 0);
                if(!TexData) {
                        std::cout << "Cubemap: Failed to load file! " << Faces[i] << std::endl;
                        stbi_image_free(TexData);
                }

                int format = 0;
                int iformat = 0;

                if (comp == 3) {
                        iformat = GL_SRGB;
                        format = GL_RGB;
                } else if (comp == 4) {
                        iformat = GL_SRGB_ALPHA;
                        format = GL_RGBA;
                }

                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, iformat, width, height, 0, format, GL_UNSIGNED_BYTE, TexData);
                stbi_image_free(TexData);
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Cubemap::Bind()
{
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, mTex);
}

void Cubemap::Unbind()
{
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
