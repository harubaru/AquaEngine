#ifndef TEXTURE_H
#define TEXTURE_H

#include <export.h>

#include <util/stb_image.h>

#include <graphics/gl3w.h>
#include <iostream>
#include <cstdlib>
#include <cstring>

#include <graphics/Graphics.h>
#include <core/ConVar.h>

API GLuint Texture_Load(const char *f);
API void Texture_Bind(GLuint texid, GLuint texunit);
API void Texture_Destroy(GLuint texid);
API void Texture_Cubemap_Bind(GLuint texid);

#endif
