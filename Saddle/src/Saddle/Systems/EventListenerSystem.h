#include "Saddle/Scene/Components.h"
#include "Saddle/Scene/Entity.h"
#include "Saddle/Events/Events.h"
#include "Saddle/Core/Input.h"

namespace Saddle {

class EventListenerSystem {
public:
    static void OnEvent(Entity& entity, Event& event)
    {
        EventListenerComponent& event_listener = entity.GetComponent<EventListenerComponent>();

        if(event.IsInCategory(EventCategory::KeyEvent))
        {
            if(event.Is(EventType::KeyPressedEvent) && event_listener.OnKeyPressed)
            {
                event_listener.OnKeyPressed(event.CastAs<KeyPressedEvent>());
            }

            else if(event.Is(EventType::KeyReleasedEvent) && event_listener.OnKeyReleased)
            {
                event_listener.OnKeyReleased(event.CastAs<KeyReleasedEvent>());
            }
        }

        else if(event.IsInCategory(EventCategory::MouseEvent))
        {
            if(event.Is(EventType::MouseButtonPressedEvent) && event_listener.OnMouseButtonPressed)
            {
                event_listener.OnMouseButtonPressed(event.CastAs<MouseButtonPressedEvent>());
            }

            if(event.Is(EventType::MouseButtonReleasedEvent) && event_listener.OnMouseButtonReleased)
            {
                event_listener.OnMouseButtonReleased(event.CastAs<MouseButtonReleasedEvent>());
            }

            if(event.Is(EventType::MouseMovedEvent) && event_listener.OnMouseMoved)
            {
                event_listener.OnMouseMoved(event.CastAs<MouseMovedEvent>());
            }

            if(event.Is(EventType::MouseScrolledEvent) && event_listener.OnMouseScrolled)
            {
                event_listener.OnMouseScrolled(event.CastAs<MouseScrolledEvent>());
            }
        }

        else if(event.IsInCategory(EventCategory::WindowEvent))
        {
            if(event.Is(EventType::WindowResizedEvent) && event_listener.OnWindowResized)
            {
                event_listener.OnWindowResized(event.CastAs<WindowResizedEvent>());
            }

            if(event.Is(EventType::WindowClosedEvent) && event_listener.OnWindowClosed)
            {
                event_listener.OnWindowClosed(event.CastAs<WindowClosedEvent>());
            }
        }

        else if(event.IsInCategory(EventCategory::ApplicationEvent))
        {
            
        }
    }
};

}