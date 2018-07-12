#ifndef AQUAENGINE_GRAPHICS_TEXTUREMANAGER_H
#define AQUAENGINE_GRAPHICS_TEXTUREMANAGER_H

#include <export.h>

#include <core/Debug.h>
#include <graphics/Texture.h>

API void TextureManager_Parse(const std::string filepath);
API GLuint TextureManager_GetTexture(const std::string texturename);
API void TextureManager_Destroy(void);

#endif
