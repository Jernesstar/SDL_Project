#include "Renderer2D.h"

#include "Renderer.h"

#include "Saddle/Text/Text.h"

namespace Saddle {

struct QuadVertex {
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TextureCoordinate;
    int32_t TextureIndex;
};

struct Renderer2DData {
    static const uint32_t MaxQuads = 150;
    static const uint32_t MaxVertices = MaxQuads * 4;
    static const uint32_t MaxIndices = MaxQuads * 6;
    static const uint32_t MaxTextureSlots = 32;

    VertexArray* QuadVertexArray;
    VertexBuffer* QuadVertexBuffer;
    IndexBuffer* QuadIndexBuffer;

    uint32_t QuadIndexCount = 0;

    Shader* QuadShader;

    QuadVertex* QuadVertexBufferBase;
    QuadVertex* QuadVertexBufferPtr;

    void* TextureSlots[MaxTextureSlots];
    uint32_t TextureSlotIndex = 0;
    uint32_t TextSlotIndex = 0;

    glm::vec4 VertexPositions[4] =
    {
        { -0.5f, -0.5f, 0.0f, 1.0f }, // Bottom left,  0
        {  0.5f, -0.5f, 0.0f, 1.0f }, // Bottom right, 1
        { -0.5f,  0.5f, 0.0f, 1.0f }, // Top left,     2
        {  0.5f,  0.5f, 0.0f, 1.0f }, // Top right,    3
    };

    glm::vec2 TextureCoords[4] =
    {
        { 0.0f, 0.0f }, // Bottom left,  0
        { 1.0f, 0.0f }, // Bottom right, 1
        { 0.0f, 1.0f }, // Top left,     2
        { 1.0f, 1.0f }, // Top right,    3
    };

    glm::vec2 TextCoords[4] = // These coordinates don't make sense
    {
        { 0.0f, 1.0f },
        { 1.0f, 1.0f },
        { 0.0f, 0.0f },
        { 1.0f, 0.0f },
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
        { "Position",          BufferDataType::Vec3 },
        { "Color",             BufferDataType::Vec4 },
        { "TextureCoordinate", BufferDataType::Vec2 },
        { "TextureIndex",      BufferDataType::Int },
    };

    s_Data.QuadIndexBuffer = new IndexBuffer(indices, Renderer2DData::MaxIndices);
    delete[] indices;

    s_Data.QuadVertexBuffer = new VertexBuffer(Renderer2DData::MaxVertices, layout);
    s_Data.QuadVertexArray = new VertexArray(s_Data.QuadVertexBuffer, s_Data.QuadIndexBuffer);

    s_Data.QuadShader = new Shader("Saddle/assets/shaders/Quad.glsl.vert", "Saddle/assets/shaders/Quad.glsl.frag");
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
    s_ViewProjMatrix = camera.GetViewProjectionMatrix();

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
    s_Data.TextSlotIndex = s_Data.MaxTextureSlots - 1;
}

void Renderer2D::Flush()
{
    std::size_t data_size = (s_Data.QuadVertexBufferPtr - s_Data.QuadVertexBufferBase) * sizeof(QuadVertex);
    s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, data_size);

    for(uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
        ((Texture2D*)s_Data.TextureSlots[i])->Bind(i);

    for(uint32_t i = s_Data.MaxTextureSlots - 1; i > s_Data.TextSlotIndex; i--)
        ((Text::CharacterQuad*)s_Data.TextureSlots[i])->Bind(i);

    s_Data.QuadShader->Bind();
    s_Data.QuadShader->SetUniformMatrix4("u_ViewProjMatrix", s_ViewProjMatrix);

    Renderer::Submit(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
}

void Renderer2D::NextBatch()
{
    Flush();
    StartBatch();
}

void Renderer2D::DrawEntity(Entity& entity, float scale)
{
    if(!entity.HasComponent<TextureComponent>() || !entity.HasComponent<TransformComponent>())
        return;

    TransformComponent transform = entity.GetComponent<TransformComponent>();
    Texture2D* texture = entity.GetComponent<TextureComponent>().Texture;

    transform.Scale = scale * glm::vec3(texture->GetWidth(), texture->GetHeight(), 1.0f);

    DrawQuad(texture, transform.GetTransform());
}

void Renderer2D::DrawEntity(Entity& entity, const glm::vec2& size)
{
    if(!entity.HasComponent<TextureComponent>() || !entity.HasComponent<TransformComponent>())
        return;

    TransformComponent transform = entity.GetComponent<TransformComponent>();
    Texture2D* texture = entity.GetComponent<TextureComponent>().Texture;

    transform.Scale = glm::vec3(size, 1.0f);

    DrawQuad(texture, transform.GetTransform());
}

void Renderer2D::DrawText(const Text& text, const glm::mat4& transform)
{
    glm::vec3 color = text.GetColor();
    for(const Text::CharacterQuad& ch : text.GetCharacters())
    {
        DrawQuad(ch, color, transform);
    }
}

void Renderer2D::DrawText(const Text& text, const glm::vec2& position, float scale)
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
                        * glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, 1.0f));
    DrawText(text, transform);
}

void Renderer2D::DrawQuad(const glm::vec4& color, const glm::vec2& position, const glm::vec2& size)
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
                        * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
    DrawQuad(color, transform);
}

void Renderer2D::DrawQuad(Texture2D* texture, const glm::vec2& position, float scale)
{
    DrawQuad(texture, position, scale * glm::vec2(texture->GetWidth(), texture->GetHeight()));
}

void Renderer2D::DrawQuad(Texture2D* texture, const glm::vec2& position, const glm::vec2& size)
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
                        * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
    DrawQuad(texture, transform);
}

void Renderer2D::DrawQuad(const glm::vec4& color, const glm::mat4& transform)
{
    if(s_Data.QuadIndexCount >= Renderer2DData::MaxIndices || s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
        NextBatch();

    for(uint32_t i = 0; i < 4; i++)
    {
        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.VertexPositions[i];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TextureIndex = -1;
        s_Data.QuadVertexBufferPtr++;
    }

    s_Data.QuadIndexCount += 6;
}

void Renderer2D::DrawQuad(Texture2D* texture, const glm::mat4& transform)
{
    if(s_Data.QuadIndexCount == Renderer2DData::MaxIndices || s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots
    || s_Data.TextSlotIndex < 0 || s_Data.TextureSlotIndex > s_Data.TextSlotIndex)
        NextBatch();

    uint32_t texture_index = 0;
    for(uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
    {
        if(*(Texture2D*)s_Data.TextureSlots[i] == *texture)
        {
            texture_index = i;
            break;
        }
    }

    if(texture_index == 0)
    {
        texture_index = s_Data.TextureSlotIndex;
        s_Data.TextureSlots[s_Data.TextureSlotIndex++] = (void*)texture;
    }

    for(uint32_t i = 0; i < 4; i++)
    {
        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.VertexPositions[i];
        s_Data.QuadVertexBufferPtr->Color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
        s_Data.QuadVertexBufferPtr->TextureCoordinate = s_Data.TextureCoords[i];
        s_Data.QuadVertexBufferPtr->TextureIndex = (int32_t)texture_index;
        s_Data.QuadVertexBufferPtr++;
    }

    s_Data.QuadIndexCount += 6;
}

void Renderer2D::DrawQuad(const Text::CharacterQuad& ch, const glm::vec3& color, const glm::mat4& transform)
{
    if(s_Data.QuadIndexCount == Renderer2DData::MaxIndices || s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots
    || s_Data.TextSlotIndex < 0 || s_Data.TextureSlotIndex > s_Data.TextSlotIndex)
        NextBatch();

    uint32_t text_index = 0;
    for(uint32_t i = s_Data.MaxTextureSlots - 1; i > s_Data.TextSlotIndex; i--)
    {
        if(*(Text::CharacterQuad*)s_Data.TextureSlots[i] == ch)
        {
            text_index = i;
            break;
        }
    }

    if(text_index == 0)
    {
        text_index = s_Data.TextSlotIndex;
        s_Data.TextureSlots[s_Data.TextSlotIndex--] = (void*)&ch;
    }

    for(uint32_t i = 0; i < 4; i++)
    {
        s_Data.QuadVertexBufferPtr->Position = transform * glm::vec4(ch.Vertices[i], 0.0f, 1.0f);
        s_Data.QuadVertexBufferPtr->Color = glm::vec4(color, 0.0f);
        s_Data.QuadVertexBufferPtr->TextureCoordinate = s_Data.TextCoords[i];
        s_Data.QuadVertexBufferPtr->TextureIndex = (int32_t)text_index;
        s_Data.QuadVertexBufferPtr++;
    }

    s_Data.QuadIndexCount += 6;
}

}