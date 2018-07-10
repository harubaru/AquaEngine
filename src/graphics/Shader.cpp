#include <graphics/Shader.h>

#include <core/Debug.h>

std::string Shader::GetShaderSource(const std::string& ShaderPath)
{
	bool Failed(false);

	std::string shader_source;
	std::ifstream filestream(ShaderPath, std::ios::in);

	if(!filestream.is_open())
	{
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
		std::cout << "Shader Error: Shaders are not correct types.\n";
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
		std::cout << "Shader failed to compile - ";	
		if (VERTEX_SHADER)
			 std::cout << this->ShaderFilePaths[0] << std::endl;
		else
			std::cout << this->ShaderFilePaths[1] << std::endl;

		std::cout << "----- Error Log -----\n" << infolog << std::endl;
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

	glDeleteShader(VertShader);
	glDeleteShader(FragShader);

	if(log_length > 0) {
		GLchar infolog[log_length];
		glGetProgramInfoLog(ShaderProgram, log_length, NULL, infolog);
		std::cout << "Shader Error: Failed to link shader: \n" << infolog << std::endl;
	}
}

Shader::Shader(const std::string& VertShaderFile, const std::string& FragShaderFile)
	: BindState(false)
{
	Load(VertShaderFile, FragShaderFile);
}

Shader::Shader(const std::string& ShaderPath)
	: BindState(false)
{
	this->Load(ShaderPath);
}

Shader::~Shader()
{
	glDetachShader(ShaderProgram, VertShader);
	glDetachShader(ShaderProgram, FragShader);

	glDeleteProgram(ShaderProgram);
}

void Shader::Load(const std::string& ShaderPath)
{
	std::string suffix[2] = {
		"vs.glsl",
		"fs.glsl"
	};

	std::string vs_path;
	vs_path.append(ShaderPath);
	vs_path.append(suffix[0]);

	std::string fs_path;
	fs_path.append(ShaderPath);
	fs_path.append(suffix[1]);

	Debug_printf(nullptr, 0, "Loading Shader: %s\n", ShaderPath.c_str());

	this->Load(vs_path, fs_path);
}

void Shader::Load(const std::string& VertShaderFile, const std::string& FragShaderFile)
{
	this->ShaderFilePaths[0] = VertShaderFile;
	this->ShaderFilePaths[1] = FragShaderFile;

	std::string VertShaderSource = GetShaderSource(VertShaderFile);
	std::string FragShaderSource = GetShaderSource(FragShaderFile);

	VertShader = CompileShader(VertShaderSource, VERTEX_SHADER);
	FragShader = CompileShader(FragShaderSource, FRAGMENT_SHADER);

	LinkShaders(VertShader, FragShader);
}

void Shader::SetModel(const glm::mat4& Model) { glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "Model"), 1, GL_FALSE, &Model[0][0]); }
void Shader::SetView(const glm::mat4& View) { glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "View"), 1, GL_FALSE, glm::value_ptr(View)); }
void Shader::SetProjection(const glm::mat4& Projection) { glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "Projection"), 1, GL_FALSE, glm::value_ptr(Projection)); }
void Shader::SetVec3(const std::string& uniform, const glm::vec3& v) { glUniform3fv(glGetUniformLocation(ShaderProgram, uniform.c_str()), 1, glm::value_ptr(v)); }
void Shader::SetFloat(const std::string& uniform, const float& f) { glUniform1f(glGetUniformLocation(ShaderProgram, uniform.c_str()), f); }
void Shader::SetInt(const std::string& uniform, const int& i) { glUniform1i(glGetUniformLocation(ShaderProgram, uniform.c_str()), i); }
void Shader::SetMat4(const std::string& uniform, const glm::mat4& m) { glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, uniform.c_str()), 1, GL_FALSE, &m[0][0]); }

void Shader::Bind()
{
	BindState = true;
	glUseProgram(ShaderProgram);
}

void Shader::Unbind()
{
	BindState = false;
	glUseProgram(0);
}
