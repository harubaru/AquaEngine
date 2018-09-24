#include <graphics/Skybox.h>

std::string suffix[6] = {
        "_right.", "_left.",
         "_top.", "_bottom.",
        "_back.", "_front."
};

GLfloat skybox_vertices[] = {
    // front
    -1.0, -1.0,  1.0,
     1.0, -1.0,  1.0,
     1.0,  1.0,  1.0,
    -1.0,  1.0,  1.0,
    // back
    -1.0, -1.0, -1.0,
     1.0, -1.0, -1.0,
     1.0,  1.0, -1.0,
    -1.0,  1.0, -1.0,
};

GLuint skybox_indices[] = {
	// front
	0, 1, 2,
	2, 3, 0,
	// right
	1, 5, 6,
	6, 2, 1,
	// back
	7, 6, 5,
	5, 4, 7,
	// left
	4, 0, 3,
	3, 7, 4,
	// bottom
	4, 5, 1,
	1, 0, 4,
	// top
	3, 2, 6,
	6, 7, 3,
};

static GLuint vao;
static GLuint vbuf = 0, ibuf = 0;

Skybox::Skybox(std::string filepath, std::string extension)
{
        std::vector<std::string> Faces;
        Faces.reserve(6);
        for (int i = 0; i < 6; i++)
                Faces.push_back(filepath + suffix[i] + extension);
        
        mSkybox.Load(Faces);
        mSkyboxShader.Load("./resources/shaders/primitives/skybox");
        
        glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbuf);
	glGenBuffers(1, &ibuf);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbuf);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), skybox_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(float), skybox_indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Skybox::~Skybox()
{
}

void Skybox::Destroy()
{
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbuf);
        glDeleteBuffers(1, &ibuf);
}

void Skybox::Draw(Camera& LocalCamera)
{
        glDisable(GL_CULL_FACE);
        glDepthFunc(GL_LEQUAL);

        mSkyboxShader.Bind();
        mSkyboxShader.SetProjection(LocalCamera.GetProjection());
        mSkyboxShader.SetView(glm::mat4(glm::mat3(LocalCamera.GetView())));

        mSkybox.Bind();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 36 * sizeof(float), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        mSkybox.Unbind();

        mSkyboxShader.Unbind();

        glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);
}
