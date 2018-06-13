#include <graphics/Mesh.h>

Mesh::Mesh() // Default Constructor
{

}

Mesh::Mesh(Vertex* vertices, const std::vector<uint32_t>& Indices) : DrawCount(Indices.size())
{
	Load(vertices, Indices);
}

Mesh::Mesh(Vertex* vertices, const std::vector<uint32_t>& Indices, size_t drawcount) : DrawCount(drawcount)
{
	Load(vertices, Indices);
}

void Mesh::Load(Vertex* vertices, const std::vector<uint32_t>& Indices)
{
	if(vertices == nullptr) {
		std::cout << "Mesh Error: Vertices point to NULL." << std::endl;
		return;
	}

	glGenVertexArrays(1, &m_VertexArrayObject);
	glBindVertexArray(m_VertexArrayObject); // bind vao

	glGenBuffers(1, &m_VertexArrayBuffer);
	glGenBuffers(1, &m_IndexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, DrawCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(GLuint), &Indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);  // vertices
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)12); // normals
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)24); // texture coordinates

	glBindVertexArray(0); // unbind vao
}

void Mesh::Load(Vertex* vertices, const std::vector<uint32_t>& Indices, size_t drawcount)
{
	DrawCount = drawcount;
	Load(vertices, Indices);
}

void Mesh::Destroy()
{
	glDeleteVertexArrays(1, &m_VertexArrayObject);
	glDeleteBuffers(1, &m_VertexArrayBuffer);
	glDeleteBuffers(1, &m_IndexBufferObject);
}

void Mesh::Draw()
{
	glBindVertexArray(m_VertexArrayObject);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glDrawElements(GL_TRIANGLES, DrawCount, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}
