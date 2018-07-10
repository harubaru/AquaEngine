#ifndef AQUAENGINE_CORE_DEBUG_H
#define AQUAENGINE_CORE_DEBUG_H

#include <export.h>

#include <graphics/gl3w.h>

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

#define LOG(X) Debug_printf(__FILE__, __LINE__, X)
#define ASSERTGL() Debug_AssertGL(__FILE__, __LINE__)

#ifdef __cplusplus
extern "C" {
#endif

API void Debug_Init(const char *fp);
API void Debug_printf(const char *file, unsigned line, const char *s, ...);
API void Debug_AssertGL(const char *file, unsigned line);
API void Debug_Kill(void);

#ifdef __cplusplus
}
#endif

#endif
