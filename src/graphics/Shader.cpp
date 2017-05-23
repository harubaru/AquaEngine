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

GLuint Shader::LinkShaders(GLuint shader1, GLuint shader2)
{
	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, shader1);
	glAttachShader(shader_program, shader2);

	int log_length;
	glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &log_length);

	if(log_length > 0) {
		GLchar infolog[log_length];
		glGetProgramInfoLog(shader_program, log_length, NULL, infolog);
		std::cout << "\nFailed to create Shader Program!\nError : \n" << infolog << std::endl;
		return 0;
	}

	return shader_program;

}

Shader::Shader(const std::string& VertShaderFile, const std::string& FragShaderFile)
{
	std::string VertShaderSource = GetShaderSource(VertShaderFile);
	 std::string FragShaderSource = GetShaderSource(FragShaderFile);

	VertShader = CompileShader(VertShaderSource, VERTEX_SHADER);
	FragShader = CompileShader(FragShaderSource, FRAGMENT_SHADER);
	
	ShaderProgram = LinkShaders(VertShader, FragShader);
}

Shader::~Shader() 
{
	glDetachShader(ShaderProgram, VertShader);
	glDetachShader(ShaderProgram, FragShader);

	glDeleteShader(VertShader);
	glDeleteShader(FragShader);

	glDeleteProgram(ShaderProgram);
}

void Shader::Bind()
{
	glUseProgram(ShaderProgram);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

