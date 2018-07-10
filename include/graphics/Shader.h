#ifndef AQUAENGINE_GRAPHICS_SHADER_H
#define AQUAENGINE_GRAPHICS_SHADER_H

#include <export.h>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <graphics/gl3w.h>
#include <graphics/glm/glm.hpp>
#include <graphics/glm/gtx/transform.hpp>
#include <graphics/glm/gtc/type_ptr.hpp>

enum gl_shadertype {
	VERTEX_SHADER = GL_VERTEX_SHADER,
	FRAGMENT_SHADER = GL_FRAGMENT_SHADER
};

class API Shader{
private:
	std::string GetShaderSource(const std::string& ShaderPath);
	GLuint CompileShader(const std::string& SourceCode, gl_shadertype shadertype);
	void LinkShaders(GLuint shader1, GLuint shader2);

	GLuint VertShader, FragShader;
	GLuint ShaderProgram;

	std::string ShaderFilePaths[2];
public:
	Shader() {}
	Shader(const std::string& VertShaderFile, const std::string& FragShaderFile);
	Shader(const std::string& ShaderPath);
	~Shader();

	void Load(const std::string& ShaderPath);
	void Load(const std::string& VertShaderFile, const std::string& FragShaderFile);

	void SetModel(const glm::mat4& Model);
	void SetView(const glm::mat4& View);
	void SetProjection(const glm::mat4& Projection);

	void SetVec3(const std::string& uniform, const glm::vec3& v);
	void SetFloat(const std::string& uniform, const float& f);
	void SetInt(const std::string& uniform, const int& i);
	void SetMat4(const std::string& uniform, const glm::mat4& m);

	void Bind();
	void Unbind();

	bool BindState;
};

#endif
