#ifndef AQUAENGINE_CORE_CONVAR_H
#define AQUAENGINE_CORE_CONVAR_H

#include <export.h>
#include <string>

class API ConVar {
public:
	ConVar() {}
	ConVar(std::string name, std::string str);
	ConVar(std::string name, float value);

	std::string name;
	std::string str;
	float value;
};

API void ConVar_LoadFile(const std::string &filepath);
API void ConVar_RegisterVariable(const ConVar &cvar);
API ConVar *ConVar_FindVariable(std::string Name);
API float ConVar_GetFloat(std::string Name);
API std::string ConVar_GetString(std::string Name);
API void ConVar_SetFloat(std::string Name, float value);
API void ConVar_SetString(std::string Name, std::string str);

#endif
