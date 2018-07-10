#ifndef AQUAENGINE_GRAPHICS_CUBEMAP_H
#define AQUAENGINE_GRAPHICS_CUBEMAP_H

#include <export.h>

#include <vector>
#include <string>
#include <iostream>
#include <graphics/gl3w.h>
#include <util/stb_image.h>

class API Cubemap {
private:
        GLuint mTex;
public:
        Cubemap() {}
        Cubemap(std::vector<std::string> Faces);
        ~Cubemap();

        void Load(std::vector<std::string> Faces);

        void Bind();
        void Unbind();
};

#endif
