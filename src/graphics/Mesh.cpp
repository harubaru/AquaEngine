#include <graphics/Mesh.h>

Mesh::Mesh(Vertex* vertices, GLsizei VertexCount) : DrawCount(VertexCount)
{
	glGenVertexArrays(1, &m_VertexArrayObject);
	glBindVertexArray(m_VertexArrayObject); // bind vao

	glGenBuffers(1, &m_VertexArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, VertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)12);

	glBindVertexArray(0); // unbind vao
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VertexArrayObject);
	glDeleteBuffers(1, &m_VertexArrayBuffer);
}

void Mesh::Draw()
{
	glBindVertexArray(m_VertexArrayObject);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawArrays(GL_TRIANGLES, 0, DrawCount);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

