#include "Scene.h"

#include "Saddle/ECS/Entity.h"
#include "Saddle/Renderer/Renderer.h"

namespace Saddle {

void Scene::Update()
{
    TimePoint time = Time::GetTime();
    TimeStep ts = time - m_LastFrameTime;
    m_LastFrameTime = time;

    // for(int i = 0; i < entities.size(); i++)
    // {
    //    if(PhysicsSystem::EntityHasDependencies(entity))
    //    {
    //        PhysicsSystem::Update(entity, ts);
    //    }
    // }
}

void Scene::Render()
{
    // Renderer::Clear();
    // for(int i = 0; i < entities.size(); i++)
    // {
    //     Entity& entity = *entities.at(i);
    //     if(entity.HasComponent<TextureComponent>() && entity.HasComponent<TransformComponent>())
    //     { 
    //         Texture2D& texture = entity.GetComponent<TextureComponent>().Texture;
    //         Transform transform = entity.GetComponent<TransformComponent>();
    //         Renderer::DrawTexture(texture, transform);
    //     }
    // }
    // Renderer::Render();
}

void Scene::Pause() { m_LastFrameTime = Time::GetTime(); }

void Scene::AddEntity(Entity& entity)
{
    entity.m_Scene = this;
}

void Scene::RemoveEntity(Entity& entity)
{
    m_Registry.RemoveEntity(entity);
}

}