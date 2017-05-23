#ifndef AQUAGL_SHADER_H
#define AQUAGL_SHADER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <GL/glew.h>

enum gl_shadertype {
	VERTEX_SHADER = GL_VERTEX_SHADER,
	FRAGMENT_SHADER = GL_FRAGMENT_SHADER
};

class Shader{
private:
	std::string GetShaderSource(const std::string& ShaderPath);
	GLuint CompileShader(const std::string& SourceCode, gl_shadertype shadertype);
	GLuint LinkShaders(GLuint shader1, GLuint shader2);
	
	GLuint VertShader, FragShader;
	GLuint ShaderProgram;
public:
	Shader(const std::string& VertShaderFile, const std::string& FragShaderFile);
	~Shader();

	void Bind();
	void Unbind();
};

#endif

