#include <graphics/Mesh.h>

Mesh::Mesh(Vertex* vertices, GLsizei VertexCount) : DrawCount(VertexCount)
{
	glGenVertexArrays(1, &m_VertexArrayObject);
	glBindVertexArray(m_VertexArrayObject); // bind vao

	glGenBuffers(NUM_BUFFERS, m_VertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffers[POSITION_POS]);
	glBufferData(GL_ARRAY_BUFFER, VertexCount * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	glBindVertexArray(0); // unbind vao
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VertexArrayObject);
	glDeleteBuffers(1, &m_VertexArrayBuffers[POSITION_POS]);
}

void Mesh::Draw()
{
	glBindVertexArray(m_VertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, DrawCount);
	glBindVertexArray(0);
}

