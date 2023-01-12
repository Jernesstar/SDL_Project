#include "Renderer2D.h"

#include "Renderer.h"

namespace Saddle {

struct QuadVertex {
    glm::vec3 Position;
    glm::vec2 TextureCoordinate;
    float TextureIndex;
};

struct Renderer2DData {
    static const uint32_t MaxQuads = 10;
    static const uint32_t MaxVertices = MaxQuads * 4;
    static const uint32_t MaxIndices = MaxQuads * 6;
    static const uint32_t MaxTextureSlots = 32;

    uint32_t QuadIndexCount = 0;

    VertexArray* QuadVertexArray;
    VertexBuffer* QuadVertexBuffer;
    IndexBuffer* QuadIndexBuffer;
    Shader* QuadShader;

    QuadVertex* QuadVertexBufferBase;
    QuadVertex* QuadVertexBufferPtr;

    Texture2D* TextureSlots[32];
    uint32_t TextureSlotIndex = 0;

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
    s_Data.QuadVertexBufferBase = new QuadVertex[Renderer2DData::MaxVertices];

    uint32_t* indices = new uint32_t[Renderer2DData::MaxIndices];

    for(uint32_t i = 0; i < Renderer2DData::MaxQuads; i++)
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
        { "VertexPosition", BufferDataType::Vec3 },
        { "TextureCoordinate", BufferDataType::Vec2 },
        { "TextureIndex", BufferDataType::Float }
    };

    s_Data.QuadIndexBuffer = new IndexBuffer(indices, Renderer2DData::MaxIndices);
    delete[] indices;

    s_Data.QuadVertexBuffer = new VertexBuffer(Renderer2DData::MaxVertices, layout);
    s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, Renderer2DData::MaxVertices);

    s_Data.QuadVertexArray = new VertexArray(s_Data.QuadVertexBuffer, s_Data.QuadIndexBuffer);
    s_Data.QuadShader = new Shader("Saddle/assets/shaders/Quad.glsl.vert", "Saddle/assets/shaders/Quad.glsl.frag");
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
    s_ViewMatrix = camera.GetViewMatrix();
    s_ProjectionMatrix = camera.GetProjectionMatrix();

    StartBatch();
}

void Renderer2D::EndScene()
{
    Flush();
}

void Renderer2D::StartBatch()
{
    s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
    s_Data.QuadIndexCount = 0;
    s_Data.TextureSlotIndex = 0;
}

void Renderer2D::Flush()
{
    uint32_t data_size = uint32_t((uint32_t*)s_Data.QuadVertexBufferPtr - (uint32_t*)s_Data.QuadVertexBufferBase);
    s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, data_size);

    for(uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
        s_Data.TextureSlots[i]->Bind(i);

    s_Data.QuadShader->Bind();
    s_Data.QuadShader->SetUniformMatrix4("u_ViewMatrix", s_ViewMatrix);
    s_Data.QuadShader->SetUniformMatrix4("u_ProjMatrix", s_ProjectionMatrix);

    Renderer::Submit(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
}

void Renderer2D::NextBatch()
{
    Flush();
    StartBatch();
}

void Renderer2D::DrawQuad(Texture2D* texture, const glm::mat4& transform)
{
    if(s_Data.QuadIndexCount >= Renderer2DData::MaxIndices || s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
        NextBatch();

    float textureIndex = 0.0f;
    for(uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
    {
        if (*s_Data.TextureSlots[i] == *texture)
        {
            textureIndex = (float)i;
            break;
        }
    }

    if(textureIndex == 0.0f)
    {
        textureIndex = (float)s_Data.TextureSlotIndex;
        s_Data.TextureSlots[s_Data.TextureSlotIndex++] = texture;
    }

    for(uint32_t i = 0; i < 4; i++)
    {
        s_Data.QuadVertexBufferPtr->Position = glm::vec3(transform * glm::vec4(s_Data.VertexPositions[i], 0, 0));
        s_Data.QuadVertexBufferPtr->TextureCoordinate = s_Data.TextureCoords[i];
        s_Data.QuadVertexBufferPtr->TextureIndex = textureIndex;
        s_Data.QuadVertexBufferPtr++;
    }

    s_Data.QuadIndexCount += 6;
}

void Renderer2D::DrawEntity(Entity& entity)
{
    if(!entity.HasComponent<TextureComponent>() || !entity.HasComponent<TransformComponent>())
        return;

    glm::mat4 transform = entity.GetComponent<TransformComponent>().GetTransfrom();
    Texture2D* texture = entity.GetComponent<TextureComponent>().Texture;

    DrawQuad(texture, transform);
}

}