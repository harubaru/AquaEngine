#include <core/ConVar.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

ConVar::ConVar(std::string name, std::string str)
{
	this->name = name;
	this->str = str;
}

ConVar::ConVar(std::string name, float value)
{
	this->name = name;
	this->value = value;
}

std::vector<ConVar> convars;

static bool isFloat(std::string str)
{
	std::istringstream iss(str);
	float f;

	iss >> std::noskipws >> f;

	return iss.eof() && !iss.fail();
}

void ConVar_LoadFile(const std::string &filepath)
{
	std::ifstream file(filepath);
	if (!file.is_open()) {
		std::cout << "ConVar: Can't open file - " << filepath << std::endl;
		return;
	}
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		if ((line == "") || (line.front() == '#')) continue;
		ConVar cvar;
		std::string val;
		if (!(iss >> cvar.name >> val)) { std::cout << "ConVar: Invalid ConVar: " << line << std::endl; continue; }

		if (isFloat(val)) {
			cvar.value = std::stof(val, nullptr);
		} else {
			cvar.str = val;
		}

		ConVar_RegisterVariable(cvar);
	}
}

void ConVar_RegisterVariable(const ConVar &cvar)
{
	convars.push_back(cvar);
}

ConVar *ConVar_FindVariable(std::string Name)
{
	for (auto &i : convars) {
		if (i.name == Name)
			return &i;
	}

	std::cout << "ConVar: Could not find variable named: " << Name << std::endl;

	return nullptr;
}

float ConVar_GetFloat(std::string Name)
{
	ConVar *cvar = ConVar_FindVariable(Name);

	if (cvar)
		return cvar->value;

	return 0.0f;
}

std::string ConVar_GetString(std::string Name)
{
	ConVar *cvar = ConVar_FindVariable(Name);

	if (cvar)
		return cvar->str;

	return "";
}

void ConVar_SetFloat(std::string Name, float value)
{
	ConVar *cvar = ConVar_FindVariable(Name);

	if (cvar)
		cvar->value = value;
}

void ConVar_SetString(std::string Name, std::string str)
{
	ConVar *cvar = ConVar_FindVariable(Name);

	if (cvar)
		cvar->str = str;
}

