#include "Renderer2D.h"

#include "Renderer.h"

namespace Saddle {

struct Vertex {
    glm::vec2 Position;
    glm::vec2 TextureCoordinate;
};

void Renderer2D::Init()
{
    const Vertex vertices[4] =
    {
        { glm::vec2(-0.5f,  0.5f), glm::vec2(0.0f, 1.0f) }, // Top left, 0
        { glm::vec2( 0.5f,  0.5f), glm::vec2(1.0f, 1.0f) }, // Top right, 1
        { glm::vec2(-0.5f, -0.5f), glm::vec2(0.0f, 0.0f) }, // Bottom left, 2
        { glm::vec2( 0.5f, -0.5f), glm::vec2(1.0f, 0.0f) }, // Bottom right, 3
    };

    unsigned int indices[6] =
    {
        3, 2, 0,
        0, 1, 3
    };

    BufferLayout layout =
    {
        { "a_VertexPosition", BufferDataType::Vec2, true },
        { "a_TextureCoordinate", BufferDataType::Vec2, true },
    };

    s_Shader = new Shader("Saddle/assets/shaders/Quad.glsl.vert", "Saddle/assets/shaders/Quad.glsl.frag");
    s_VertexArray = new VertexArray(vertices, layout, indices);

    s_Shader->Bind();
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
    s_ViewMatrix = camera.GetViewMatrix();
    s_ProjectionMatrix = camera.GetProjectionMatrix();
}

void Renderer2D::DrawTexture(Texture2D& texture, const glm::mat4& transform)
{
    texture.Bind(0);
    s_Shader->SetUniformInt("u_Texture", 0);
    s_Shader->SetUniformMatrix4("u_ModelMatrix", transform);

    Renderer::Submit(*s_VertexArray);
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