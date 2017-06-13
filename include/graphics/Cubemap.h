#ifndef AQUAGL_CUBEMAP_H
#define AQUAGL_CUBEMAP_H

#include <vector>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <util/stb_image.h>

class Cubemap {
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
