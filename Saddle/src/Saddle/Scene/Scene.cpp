#include "Scene.h"
#include "Entity.h"

#include "Saddle/Renderer/Renderer.h"
#include "Saddle/Systems/EventListenerSystem.h"
#include "Saddle/Systems/PhysicsSystem.h"

namespace Saddle {

Scene::Scene() : entities() { }
Scene::~Scene() { EventSystem::Reset(); }

void Scene::Update()
{
    TimePoint time = Time::GetTime();
    TimeStep ts = time - (m_LastFrameTime != 0 ? m_LastFrameTime : Time::GetTime());
    m_LastFrameTime = time;

    for(int i = 0; i < entities.size(); i++)
    {
        Entity& entity = *entities.at(i);
        if(PhysicsSystem::HasDependencies(entity))
        {
            PhysicsSystem::Update(entity, ts);
        }
    }
}

void Scene::Render()
{
    Renderer::Clear();
    for(int i = 0; i < entities.size(); i++)
    {
        Entity& entity = *entities.at(i);
        if(entity.HasComponent<TextureComponent>() && entity.HasComponent<TransformComponent>())
        { 
            Texture2D& texture = entity.GetComponent<TextureComponent>().Texture;
            Transform transform = entity.GetComponent<TransformComponent>();
            Renderer::DrawTexture(texture, transform);
        }
    }
    Renderer::Render();
}

void Scene::Pause() { m_LastFrameTime = Time::GetTime(); }

void Scene::AddEntity(Entity& entity)
{
    entities.push_back(&entity);
    entity.m_Scene = this;

    // Note: Place this in a method that regularly updates all the Entities
    if(entity.HasComponent<EventListenerComponent>())
    {
        EventSystem::RegisterEventListener<Event>(
            [&entity](Event& event) {
                EventListenerSystem::OnEvent(entity, event);
            }
        );
    }
}

std::vector<Entity*> Scene::Query(std::function<bool(const Entity& entity)> predicate)
{
    std::vector<Entity*> result = { };
    for(int i = 0; i < entities.size(); i++)
    {
        Entity& entity = *entities.at(i);
        if(predicate(entity))
        {
            result.push_back(&entity);
        }
    }
    return result;
}

}