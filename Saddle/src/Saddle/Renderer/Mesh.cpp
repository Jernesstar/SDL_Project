#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "Saddle/Core/Log.h"
#include "Saddle/Core/Assert.h"

namespace Saddle {

Mesh::Mesh(const std::string& path)
    : m_Path(path)
{
    if(path == "" || path.find_first_not_of(" ") == std::string::npos)
        return;

    LoadMesh(path);
}

Mesh::~Mesh() { Clear(); }

void Mesh::Clear()
{
    m_SubMeshes.clear();
    m_Materials.clear();

    m_Positions.clear();
    m_Normals.clear();
    m_TextureCoords.clear();
    m_Indices.clear();

    m_Buffers[BufferIndex::Position].reset();
    m_Buffers[BufferIndex::TextureCoordinate].reset();
    m_Buffers[BufferIndex::Normal].reset();
    m_IndexBuffer.reset();
    m_VertexArray.reset();
}

void Mesh::LoadMesh(const std::string& path)
{
    Clear();

    Assimp::Importer imp;
    uint32_t load_flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices;
    const aiScene* scene = imp.ReadFile(path.c_str(), load_flags);

    if(!scene)
        SADDLE_CORE_ASSERT_ARGS(false, "Error importing from %s: %s", path.c_str(), imp.GetErrorString());

    m_Path = path;
    m_SubMeshes.resize(scene->mNumMeshes);
    m_Materials.resize(scene->mNumMaterials);

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

    for(uint32_t i = 0; i < scene->mNumMaterials; i++)
        LoadMaterial(scene->mMaterials[i], path, i);

    BufferLayout l1({ { "Position",          BufferDataType::Vec3, false } }, false);
    BufferLayout l2({ { "TextureCoordinate", BufferDataType::Vec2, false } }, false);
    BufferLayout l3({ { "Normal",            BufferDataType::Vec3, false } }, false);

    m_Buffers[BufferIndex::Position]          = std::make_unique<VertexBuffer>(m_Positions.size(), l1);
    m_Buffers[BufferIndex::TextureCoordinate] = std::make_unique<VertexBuffer>(m_TextureCoords.size(), l2);
    m_Buffers[BufferIndex::Normal]            = std::make_unique<VertexBuffer>(m_Normals.size(), l3);

    m_Buffers[BufferIndex::Position]->SetData(&m_Positions[0], m_Positions.size());
    m_Buffers[BufferIndex::TextureCoordinate]->SetData(&m_TextureCoords[0], m_TextureCoords.size());
    m_Buffers[BufferIndex::Normal]->SetData(&m_Normals[0], m_Normals.size());

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
        m_TextureCoords.push_back(glm::vec2(texture_coord.x, texture_coord.y));
    }

    for(uint32_t i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace& face = mesh->mFaces[i];
        m_Indices.push_back(face.mIndices[0]);
        m_Indices.push_back(face.mIndices[1]);
        m_Indices.push_back(face.mIndices[2]);
    }
}

void Mesh::LoadMaterial(const aiMaterial* material, const std::string& path, uint32_t index)
{
    std::size_t slash_index = path.find_last_of("/");
    std::string dir;

    if(slash_index == std::string::npos)
        dir = ".";
    else if(slash_index == 0)
        dir = "/";
    else
        dir = path.substr(0, slash_index);

    m_Materials[index].Diffuse.reset(LoadTexture(material, dir, aiTextureType_DIFFUSE));
    m_Materials[index].Specular.reset(LoadTexture(material, dir, aiTextureType_SPECULAR));
}

Texture2D* Mesh::LoadTexture(const aiMaterial* material, const std::string& dir, aiTextureType type)
{
    if(material->GetTextureCount(type) == 0)
        return nullptr;

    // Todo: Maybe load all possible textures ?
    aiString path;
    if(material->GetTexture(type, 0, &path) == AI_FAILURE)
        return nullptr;

    std::string p(path.data);
    if(p.substr(0, 2) == "./")
        p = p.substr(2, p.size() - 2);

    std::string full_path = dir + "/" + p;
    return new Texture2D(full_path);
}

}