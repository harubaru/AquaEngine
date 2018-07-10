#ifndef AQUAENGINE_EXPORT_H
#define AQUAENGINE_EXPORT_H

#ifdef _WIN32
#ifndef DLL_BUILD
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif
#else
#define API 
#endif 

#ifdef main
#undef main
#endif

#endif
