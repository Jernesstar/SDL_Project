#include "Scene.h"
#include "Entity.h"

#include "Saddle/Renderer/Renderer.h"
#include "Saddle/Systems/EventListenerSystem.h"

namespace Saddle {

Scene::Scene() : entities() { }
Scene::~Scene() { EventSystem::Reset(); }

void Scene::OnUpdate()
{
    float time = TimeStep::GetTime();
    TimeStep ts = time - m_LastFrameTime;
    m_LastFrameTime = time;

    // for(int i = 0; i < entities.size(); i++)
    // {
    //     Entity& entity = *entities.at(i);
    // }
}

void Scene::OnSceneRender()
{
    Renderer::Clear();
    for(int i = 0; i < entities.size(); i++)
    {
        Entity& entity = *entities.at(i);
        if(entity.HasComponent<TextureComponent>() && entity.HasComponent<TransformComponent>())
        { 
            Texture2D& texture = entity.GetComponent<TextureComponent>().Texture;
            Transform coordinate = entity.GetComponent<TransformComponent>();
            Renderer::DrawTexture(texture, coordinate);
        }
    }
    Renderer::Render();
}

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