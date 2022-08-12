#include "Scene.h"
#include "Entity.h"

#include "Renderer.h"
#include "EventListenerSystem.h"

namespace Saddle {

Scene::Scene() : entities() { }
Scene::~Scene() { }

// void Scene::OnUpdate(TimeStep step)
// {
//     for(int i = 0; i < entities.size(); i++)
//     {
//         Entity& entity = *entities.at(i);
//         if(entity.HasComponent<EventListenerComponent>())
//             EventListenerSystem::OnEvent(entity);
//     }
// }

void Scene::OnSceneRender()
{
    for(int i = 0; i < entities.size(); i++)
    {
        Entity& entity = *entities.at(i);
        if(entity.HasComponent<TextureComponent>())
        {
            auto& rect_component = entity.GetComponent<RectComponent>();
            auto& coordinate = entity.GetComponent<Coordinate2DComponent>();
            auto& texture = entity.GetComponent<TextureComponent>();
            SDL_Rect rect = { coordinate.x, coordinate.y, rect_component.width, rect_component.height };
            Renderer::DrawTexture(rect, texture.texture);
        }
    }
    Renderer::Render();
}

void Scene::AddEntity(Entity& entity)
{
    entities.push_back(&entity);
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