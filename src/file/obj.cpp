#include <file/obj.h>

bool ParseOBJFile(const std::string& FilePath, std::vector<glm::vec3>& processed_vertices, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& texcoords, std::vector<unsigned int> vertexindices)
{
	std::vector<glm::vec3> vertices;
	std::vector<int> texindices;
	std::vector<int> normalindices;

	std::ifstream OBJFile;
	OBJFile.open(FilePath, std::ios::in);

	if(!OBJFile.is_open()) {
		std::cout << "[Mesh] ERROR : Unable to open file! - File: " << FilePath << std::endl;
		return false;
	}
	
	std::string line;
	while(getline(OBJFile, line)) {
		std::string begin = line.substr(0, 2);

		if(begin == "v ") {
			std::istringstream v(line.substr(2));
			float x, y, z;
			glm::vec3 vertex;

			v >> x;
			v >> y;
			v >> z;

			vertex = glm::vec3(x, y, z);
			vertices.push_back(vertex);
		}

		else if (begin == "vt") {
			std::istringstream v(line.substr(2));
			float x, y;
			glm::vec2 texcoord;
			
			v >> x;
			v >> y;

			texcoord = glm::vec2(x, y);
			texcoords.push_back(texcoord);
		}

		else if (begin == "vn") {
			std::istringstream v(line.substr(2));
			float x, y, z;
			glm::vec3 normal;

			v >> x;
			v >> y;
			v >> z;

			normal = glm::vec3(x, y, z);
			normals.push_back(normal);
		}

		else if (begin == "f ") {
			unsigned int vertIndex[3], uvIndex[3], normalIndex[3];

			const char* str_line = line.c_str();
			sscanf(str_line, "f %i/%i/%i %i/%i/%i %i/%i/%i\n", 
					&vertIndex[0], &uvIndex[0], &normalIndex[0],
					&vertIndex[1], &uvIndex[1], &normalIndex[1],
					&vertIndex[2], &uvIndex[2], &normalIndex[2]);

			vertexindices.push_back(vertIndex[0]);
			vertexindices.push_back(vertIndex[1]);
			vertexindices.push_back(vertIndex[2]);

			texindices.push_back(uvIndex[0]);
			texindices.push_back(uvIndex[1]);
			texindices.push_back(uvIndex[2]);

			normalindices.push_back(normalIndex[0]);
			normalindices.push_back(normalIndex[1]);
			normalindices.push_back(normalIndex[2]);
		}
	}

	// process data
	for(unsigned int i = 0; i < vertexindices.size(); i++) {
		int VertIndex = vertexindices[i];
		glm::vec3 vertex = vertices[VertIndex - 1];
		processed_vertices.push_back(vertex);
	}

	OBJFile.close();
	return true;
}

