#include <graphics/Model.h>

Model::Model(const std::string& FilePath)
{
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(FilePath, aiProcess_Triangulate | aiProcess_FlipUVs);

        if(!scene || (scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode) {
                std::cout << "Assimp Error: " << importer.GetErrorString() << std::endl;
                MeshFail = true;
                return;
        }
        MeshFail = false;

        this->MeshCount = scene->mRootNode->mNumMeshes;
        this->FilePath = FilePath;

        Meshes.reserve(MeshCount + 1);

        this->ProcessNode(scene->mRootNode, scene);
}

Model::~Model()
{
        if(!MeshFail) {
                for(uint32_t i = 0; i < MeshCount; i++)
                        Meshes[i].Destroy();
        }
}

void Model::ProcessNode(aiNode* Node, const aiScene* Scene)
{

        for(uint32_t i = 0; i < Node->mNumMeshes; i++) {
                aiMesh* mesh = Scene->mMeshes[Node->mMeshes[i]];
                Meshes.push_back(ProcessMesh(mesh));
        }

        for(uint32_t i = 0; i < Node->mNumChildren; i++) {
                ProcessNode(Node->mChildren[i], Scene);
        }
}

Mesh Model::ProcessMesh(aiMesh* mesh)
{
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

        for(uint32_t i = 0; i < mesh->mNumVertices; i++) {
                Vertex vertex;

                vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
                vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

                if(mesh->mTextureCoords[0]) {
                        glm::vec2 texcoord;
                        texcoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y );
                        vertex.texcoord = texcoord;
                } else {
                        vertex.texcoord = glm::vec2(0.0f, 0.0f);
                }

                vertices.push_back(vertex);
        }

        for(uint32_t f_index = 0; f_index < mesh->mNumFaces; f_index++) {
                aiFace face = mesh->mFaces[f_index];

                for(unsigned int i_index = 0; i_index < face.mNumIndices; i_index++) {
                        indices.push_back(face.mIndices[i_index]);
                }
        }

        if(mesh->mMaterialIndex > 0) { // TODO: process materials.

        }

        return Mesh(&vertices[0], indices);
}

void Model::Render()
{
        for(unsigned int i = 0; i < Meshes.size(); i++) {
                Meshes[i].Draw();
        }
}
