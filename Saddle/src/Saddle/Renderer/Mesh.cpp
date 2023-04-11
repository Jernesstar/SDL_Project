#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "Saddle/Core/Log.h"
#include "Saddle/Core/Assert.h"

namespace Saddle {

Mesh::Mesh(const std::string& path)
{
    if(path == "")
        return;
    LoadMesh(path);
}

void Mesh::LoadMesh(const std::string& path)
{
    Assimp::Importer imp;
    uint32_t load_flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices;
    const aiScene* scene = imp.ReadFile(path.c_str(), load_flags);

    if(!scene)
        SADDLE_CORE_ASSERT_ARGS(false, "Error importing from %s: %s", path.c_str(), imp.GetErrorString())
    
    m_SubMeshes.resize(scene->mNumMeshes);
    m_Textures.resize(scene->mNumMaterials);

    uint32_t vertex_count = 0;
    uint32_t index_count = 0;

    for(uint32_t i = 0; i < m_SubMeshes.size(); i++)
    {
        aiMesh* in_mesh = scene->mMeshes[i];
        SubMesh& out_mesh = m_SubMeshes[i];
        out_mesh.MaterialIndex = in_mesh->mMaterialIndex;
        out_mesh.IndexCount = in_mesh->mNumFaces * 3;
        out_mesh.BaseVertex = vertex_count;
        out_mesh.BaseIndex = index_count;

        vertex_count += in_mesh->mNumVertices;
        index_count += out_mesh.IndexCount;
    }

    m_Positions.reserve(vertex_count);
    m_TextureCoords.reserve(vertex_count);
    m_Normals.reserve(vertex_count);
    m_Indices.reserve(index_count);

    for(uint32_t i = 0; i < m_SubMeshes.size(); i++)
        LoadSubMesh(scene->mMeshes[i]);

    std::size_t slash_index = path.find_last_of("/");
    std::string dir;

    if(slash_index == std::string::npos)
        dir = ".";
    else if(slash_index == 0)
        dir = "/";
    else
        dir = path.substr(0, slash_index);

    for(uint32_t i = 0; i < scene->mNumMaterials; i++)
        LoadMaterial(scene, path, dir, i);

    BufferLayout l1({ { "Position",          BufferDataType::Vec3, false } }, false);
    BufferLayout l2({ { "TextureCoordinate", BufferDataType::Vec3, false } }, false);
    BufferLayout l3({ { "Normal",            BufferDataType::Vec3, false } }, false);

    m_Buffers[BufferIndex::Position]          = std::make_unique<VertexBuffer>(m_Positions.size(), l1);
    m_Buffers[BufferIndex::TextureCoordinate] = std::make_unique<VertexBuffer>(m_TextureCoords.size(), l2);
    m_Buffers[BufferIndex::Normal]            = std::make_unique<VertexBuffer>(m_Normals.size(), l3);

    m_Buffers[BufferIndex::Position]->SetData(&m_Positions[0], m_Positions.size() * sizeof(glm::vec3));
    m_Buffers[BufferIndex::TextureCoordinate]->SetData(&m_TextureCoords[0], m_TextureCoords.size() * sizeof(glm::vec2));
    m_Buffers[BufferIndex::Normal]->SetData(&m_Normals[0], m_Normals.size() * sizeof(glm::vec3));

    m_IndexBuffer = std::make_unique<IndexBuffer>(&m_Indices[0], m_Indices.size());

    m_VertexArray = std::make_unique<VertexArray>();
    m_VertexArray->SetIndexBuffer(m_IndexBuffer.get());
    m_VertexArray->AddVertexBuffer(m_Buffers[BufferIndex::Position].get());
    m_VertexArray->AddVertexBuffer(m_Buffers[BufferIndex::TextureCoordinate].get());
    m_VertexArray->AddVertexBuffer(m_Buffers[BufferIndex::Normal].get());
}

void Mesh::LoadSubMesh(const aiMesh* mesh)
{
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for(uint32_t i = 0; i < mesh->mNumVertices; i++)
    {
        const aiVector3D& position = mesh->mVertices[i];
        const aiVector3D& normal = mesh->mNormals[i];
        const aiVector3D& texture_coord = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i] : Zero3D;

        m_Positions.push_back(glm::vec3(position.x, position.y, position.z));
        m_Normals.push_back(glm::vec3(normal.x, normal.y, normal.z));
        m_TextureCoords.push_back(glm::vec2(normal.x, normal.y));
    }

    for(uint32_t i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace& face = mesh->mFaces[i];
        m_Indices.push_back(face.mIndices[0]);
        m_Indices.push_back(face.mIndices[1]);
        m_Indices.push_back(face.mIndices[2]);
    }
}

void Mesh::LoadMaterial(const aiScene* scene, const std::string& path, const std::string& dir, uint32_t index)
{
    const aiMaterial* material = scene->mMaterials[index];
    m_Textures[index] = nullptr;

    if(material->GetTextureCount(aiTextureType_DIFFUSE) == 0)
        return;

    aiString texture_path;
    if(material->GetTexture(aiTextureType_DIFFUSE, 0, &texture_path) == AI_FAILURE)
        return;

    std::string p(texture_path.data);
    if(p.substr(0, 2) == ".\\")
        p = p.substr(2, p.size() - 2);

    std::string full_path = dir + "/" + p;
    m_Textures[index] = new Texture2D(full_path);
}

}