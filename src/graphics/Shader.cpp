#include <graphics/Shader.h>

std::string Shader::GetShaderSource(const std::string& ShaderPath)
{
	bool Failed(false);

	std::string shader_source;
	std::ifstream filestream(ShaderPath, std::ios::in);

	if(!filestream.is_open())
	{
		std::cout << "File not found! Path: " << ShaderPath << std::endl;
		Failed = true;
	} else {
		std::string line("");
		while(!filestream.eof()) {
			std::getline(filestream, line);
			shader_source.append(line + "\n");
		}
	}

	filestream.close();
	if(Failed) return std::string("");
	else return shader_source;
}

GLuint Shader::CompileShader(const std::string& SourceCode, gl_shadertype shadertype)
{
	GLuint shader;

	switch(shadertype) {
		case VERTEX_SHADER:
			shader = glCreateShader(VERTEX_SHADER);
			break;

		case FRAGMENT_SHADER:
			shader = glCreateShader(FRAGMENT_SHADER);
			break;

		default:
			shader = 0; // will be handled later in code
			break;
	}

	if(!glIsShader(shader)) {
		std::cout << "Invalid shadertype!\n";
		return 0;
	}

	const char *c_str = SourceCode.c_str();
	glShaderSource(shader, 1, &c_str, NULL);
	glCompileShader(shader);

	int log_length;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

	if (log_length > 0) {
		GLchar infolog[log_length];
		glGetShaderInfoLog(shader, log_length, NULL, infolog);
		std::cout << "Shader failed to compile!\n" << infolog << std::endl;
	}
	return shader;
}

void Shader::LinkShaders(GLuint shader1, GLuint shader2)
{
	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, shader1);
	glAttachShader(ShaderProgram, shader2);

	glLinkProgram(ShaderProgram);

	int log_length;
	glGetProgramiv(ShaderProgram, GL_INFO_LOG_LENGTH, &log_length);

	if(log_length > 0) {
		GLchar infolog[log_length];
		glGetProgramInfoLog(ShaderProgram, log_length, NULL, infolog);
		std::cout << "\nFailed to create Shader Program!\nError : \n" << infolog << std::endl;
	}
}

Shader::Shader(const std::string& VertShaderFile, const std::string& FragShaderFile)
{
	std::string VertShaderSource = GetShaderSource(VertShaderFile);
	std::string FragShaderSource = GetShaderSource(FragShaderFile);

	VertShader = CompileShader(VertShaderSource, VERTEX_SHADER);
	FragShader = CompileShader(FragShaderSource, FRAGMENT_SHADER);

	LinkShaders(VertShader, FragShader);
}

Shader::~Shader()
{
	glDetachShader(ShaderProgram, VertShader);
	glDetachShader(ShaderProgram, FragShader);

	glDeleteShader(VertShader);
	glDeleteShader(FragShader);

	glDeleteProgram(ShaderProgram);
}

void Shader::SetModel(const glm::mat4& Model)
{
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "Model"), 1, GL_FALSE, glm::value_ptr(Model));
}

void Shader::SetView(const glm::mat4& View)
{
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "View"), 1, GL_FALSE, glm::value_ptr(View));
}

void Shader::SetProjection(const glm::mat4& Projection)
{
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "Projection"), 1, GL_FALSE, glm::value_ptr(Projection));
}

void Shader::SetCameraPos(const glm::vec3& CameraPos)
{
	glUniform3fv(glGetUniformLocation(ShaderProgram, "CameraPos"), 1, glm::value_ptr(CameraPos));
}

void Shader::SetQuadColor(const glm::vec4& Color)
{
	glUniform4fv(glGetUniformLocation(ShaderProgram, "QuadColor"), 1, glm::value_ptr(Color));
}

void Shader::Bind()
{
	glUseProgram(ShaderProgram);
}

void Shader::Unbind()
{
	glUseProgram(0);
}
