#include "Renderer2D.h"

#include "Renderer.h"

namespace Saddle {

struct QuadVertex {
    glm::vec2 Position;
    glm::vec2 TextureCoordinate;
};

struct Renderer2DData {
    static const uint32_t MaxQuads = 1;
    static const uint32_t MaxVertices = MaxQuads * 4;
    static const uint32_t MaxIndices = MaxQuads * 6;

    VertexArray* QuadVertexArray;
    VertexBuffer* QuadVertexBuffer;
    IndexBuffer* QuadIndexBuffer;
    Shader* QuadShader;

    QuadVertex* QuadVertexBufferBase;

    glm::vec2 VertexPositions[4] =
    {
        { -0.5f, -0.5f }, // Bottom left,  0
        {  0.5f, -0.5f }, // Bottom right, 1
        { -0.5f,  0.5f }, // Top left,     2
        {  0.5f,  0.5f }, // Top right,    3
    };

    glm::vec2 TextureCoords[4] =
    {
        { 0.0f, 0.0f }, // Bottom left,  0
        { 1.0f, 0.0f }, // Bottom right, 1
        { 0.0f, 1.0f }, // Top left,     2
        { 1.0f, 1.0f }, // Top right,    3
    };
};

static Renderer2DData s_Data;

void Renderer2D::Init()
{
    s_Data.QuadVertexBufferBase = new QuadVertex[Renderer2DData::MaxVertices]
    {
        { glm::vec2(-0.5f, -0.5f), glm::vec2(0.0f, 0.0f) }, // Bottom left,  0
        { glm::vec2( 0.5f, -0.5f), glm::vec2(1.0f, 0.0f) }, // Bottom right, 1
        { glm::vec2(-0.5f,  0.5f), glm::vec2(0.0f, 1.0f) }, // Top left,     2
        { glm::vec2( 0.5f,  0.5f), glm::vec2(1.0f, 1.0f) }, // Top right,    3
    };

    uint32_t* indices = new uint32_t[Renderer2DData::MaxIndices];

    for(size_t i = 0; i < Renderer2DData::MaxQuads; i++)
    {
        indices[6*i + 0] = 4*i + 0;
        indices[6*i + 1] = 4*i + 2;
        indices[6*i + 2] = 4*i + 3;

        indices[6*i + 3] = 4*i + 3;
        indices[6*i + 4] = 4*i + 1;
        indices[6*i + 5] = 4*i + 0;
    }

    BufferLayout layout =
    {
        { "a_VertexPosition", BufferDataType::Vec2, true },
        { "a_TextureCoordinate", BufferDataType::Vec2, true },
    };

    s_Data.QuadIndexBuffer = new IndexBuffer(indices, Renderer2DData::MaxIndices);

    s_Data.QuadVertexBuffer = new VertexBuffer(Renderer2DData::MaxVertices, layout);
    s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, Renderer2DData::MaxVertices);

    s_Data.QuadVertexArray = new VertexArray(s_Data.QuadVertexBuffer, s_Data.QuadIndexBuffer);
    s_Data.QuadShader = new Shader("Saddle/assets/shaders/Quad.glsl.vert", "Saddle/assets/shaders/Quad.glsl.frag");
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
    s_ViewMatrix = camera.GetViewMatrix();
    s_ProjectionMatrix = camera.GetProjectionMatrix();

    s_Data.QuadShader->Bind();
    s_Data.QuadShader->SetUniformMatrix4("u_ViewMatrix", s_ViewMatrix);
    s_Data.QuadShader->SetUniformMatrix4("u_ProjMatrix", s_ProjectionMatrix);
}

void Renderer2D::DrawTexture(Texture2D& texture, const glm::mat4& transform)
{
    texture.Bind(1);
    s_Data.QuadShader->SetUniformInt("u_Texture", 1);
    s_Data.QuadShader->SetUniformMatrix4("u_ModelMatrix", transform);

    Renderer::Submit(s_Data.QuadVertexArray);
}

void Renderer2D::DrawEntity(Entity& entity)
{
    if(!entity.HasComponent<TextureComponent>() || !entity.HasComponent<TransformComponent>())
        return;

    glm::mat4 transform = entity.GetComponent<TransformComponent>().GetTransfrom();
    Texture2D& texture = entity.GetComponent<TextureComponent>().Texture;

    DrawTexture(texture, transform);
}

}