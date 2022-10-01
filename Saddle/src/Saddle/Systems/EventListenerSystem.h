#include "Saddle/Core/Assert.h"
#include "Saddle/Scene/Components.h"
#include "Saddle/Scene/Entity.h"
#include "Saddle/Events/Events.h"
#include "Saddle/Core/Input.h"

namespace Saddle {

struct EventListenerSystemDependencies {
    EventListenerComponent* event_listener_component;
};

class EventListenerSystem {
public:
    static void OnEvent(Entity& entity, Event& event)
    {
        SADDLE_CORE_ASSERT(HasDependencies(entity));
        auto [event_listener] = GetDependencies(entity);

        if(event.IsInCategory(EventCategory::Key))
        {
            if(event.Is(EventType::KeyPressed) && event_listener->OnKeyPressed)
            {
                event_listener->OnKeyPressed(event.As<KeyPressedEvent>());
            }

            else if(event.Is(EventType::KeyReleased) && event_listener->OnKeyReleased)
            {
                event_listener->OnKeyReleased(event.As<KeyReleasedEvent>());
            }
        }

        else if(event.IsInCategory(EventCategory::Mouse))
        {
            if(event.Is(EventType::MouseButtonPressed) && event_listener->OnMouseButtonPressed)
            {
                event_listener->OnMouseButtonPressed(event.As<MouseButtonPressedEvent>());
            }

            if(event.Is(EventType::MouseButtonReleased) && event_listener->OnMouseButtonReleased)
            {
                event_listener->OnMouseButtonReleased(event.As<MouseButtonReleasedEvent>());
            }

            if(event.Is(EventType::MouseMoved) && event_listener->OnMouseMoved)
            {
                event_listener->OnMouseMoved(event.As<MouseMovedEvent>());
            }

            if(event.Is(EventType::MouseScrolled) && event_listener->OnMouseScrolled)
            {
                event_listener->OnMouseScrolled(event.As<MouseScrolledEvent>());
            }
        }

        else if(event.IsInCategory(EventCategory::Window))
        {
            if(event.Is(EventType::WindowResized) && event_listener->OnWindowResized)
            {
                event_listener->OnWindowResized(event.As<WindowResizedEvent>());
            }

            if(event.Is(EventType::WindowClosed) && event_listener->OnWindowClosed)
            {
                event_listener->OnWindowClosed(event.As<WindowClosedEvent>());
            }
        }

        else if(event.IsInCategory(EventCategory::Application))
        {
            
        }
    }

    static bool HasDependencies(Entity& entity)
    {
        return entity.HasComponent<EventListenerComponent>();
    }

private:
    EventListenerSystem() = delete;
    ~EventListenerSystem() = delete;

    static EventListenerSystemDependencies GetDependencies(Entity& entity)
    {
        return { &entity.GetComponent<EventListenerComponent>() };
    }
};

}