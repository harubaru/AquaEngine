#include <cstdlib>

#include <graphics/Map.h>

MapFace::MapFace(std::vector<GLushort> indices)
{
	Load(indices);
}

void MapFace::Load(std::vector<GLushort> indices)
{
	glGenVertexArrays(1, &m_VertexArrayObject);
	glBindVertexArray(m_VertexArrayObject);

	glGenBuffers(1, &m_ElementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	DrawCount = indices.size();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);  // vertices
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)12); // normals
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)24); // texture coordinates

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void MapFace::Destroy()
{
	glDeleteVertexArrays(1, &m_VertexArrayObject);
	glDeleteBuffers(1, &m_ElementBufferObject);
}

void MapFace::Draw()
{
	glBindVertexArray(m_VertexArrayObject);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glDrawElements(GL_TRIANGLE_STRIP, DrawCount, GL_UNSIGNED_SHORT, 0);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

Map::Map(BSPParser *parser)
{
	Load(parser);
}

void Map::Load(BSPParser *parser)
{
	if(!parser) {
		LOG("Map Error: Map points to NULL.\n");
		return;
	}

	std::vector<Vertex> vertices;

	for (auto &i : parser->vertices) {
		Vertex v;
		v.position = i;

		vertices.push_back(v);
	}

	glGenBuffers(1, &m_VertexArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	for (bsp_face_t face : parser->map_faces) {
		std::vector<GLushort> indices;
		for (size_t i = face.first_edge; i < face.first_edge + face.num_edges; i++) {
			unsigned short int edge1, edge2;

			bsp_surfedge_t surfedge = parser->map_surfedges[i];
			bsp_edge_t edge = parser->map_edges[abs(surfedge)];

			if (surfedge < 0) {
				edge1 = edge.v[0];
				edge2 = edge.v[1];
			} else {
				edge1 = edge.v[1];
				edge2 = edge.v[0];
			}

			indices.push_back(edge1);
			indices.push_back(edge2);
		}

		mapfaces.push_back(MapFace(indices));
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind vbo
}

void Map::Destroy()
{
	for (auto &i : mapfaces)
		i.Destroy();

	glDeleteBuffers(1, &m_VertexArrayBuffer);
}

void Map::Render(Shader &shader)
{
	glm::mat4 model(1);
	model = glm::rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.25f));

	shader.SetModel(model);
	
	for (auto &i : mapfaces)
		i.Draw();
}
