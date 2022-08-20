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
            if(event.Is(EventType::MouseButtonPressedEvent) || event.Is(EventType::MouseButtonReleasedEvent))
            {
                Coordinate2DComponent& coordinate = entity.GetComponent<Coordinate2DComponent>();
                RectComponent& rect = entity.GetComponent<RectComponent>();

                // Check if the entity was clicked on
                auto [mouse_x, mouse_y] = Input::GetMousePosition();
                bool x_coordinate_is_in_bound = coordinate.x <= mouse_x && mouse_x <= coordinate.x + rect.Width;
                bool y_coordinate_is_in_bound = coordinate.y <= mouse_y && mouse_y <= coordinate.y + rect.Height;

                if(x_coordinate_is_in_bound && y_coordinate_is_in_bound)
                {
                    if(event.Is(EventType::MouseButtonPressedEvent) && event_listener.OnMouseButtonPressed)
                    {
                        event_listener.OnMouseButtonPressed(event.CastAs<MouseButtonPressedEvent>());
                    }

                    if(event.Is(EventType::MouseButtonReleasedEvent) && event_listener.OnMouseButtonReleased)
                    {
                        event_listener.OnMouseButtonReleased(event.CastAs<MouseButtonReleasedEvent>());
                    }
                }
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

        else if(event.IsInCategory(EventCategory::ApplicationEvent))
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
    }
};

}