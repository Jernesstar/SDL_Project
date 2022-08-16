#include "Events.h"

#include "Components.h"
#include "Entity.h"

#include "Input.h"

namespace Saddle {

class EventListenerSystem {

public:
    static void OnEvent(Entity& entity, Event event)
    {
        EventListenerComponent& event_listener = entity.GetComponent<EventListenerComponent>();

        if(event.IsInCategory(EventCategory::MouseEvent))
        {
            Coordinate2DComponent& coordinate = entity.GetComponent<Coordinate2DComponent>();
            RectComponent& rect = entity.GetComponent<RectComponent>();

            auto [mouse_x, mouse_y] = Input::GetMousePosition();
            bool x_coordinate_is_in_bound = coordinate.x <= mouse_x && mouse_x <= coordinate.x + rect.Width;
            bool y_coordinate_is_in_bound = coordinate.y <= mouse_y && mouse_y <= coordinate.y + rect.Width;

            if(x_coordinate_is_in_bound && y_coordinate_is_in_bound)
            {
                if(event.Is(EventType::MouseButtonPressedEvent) && 
                    event_listener.EventCallbacks[EventType::MouseButtonPressedEvent])
                {
                    event_listener.EventCallbacks[EventType::MouseButtonPressedEvent](event);
                }

                if(event.Is(EventType::MouseButtonReleasedEvent) &&
                    event_listener.EventCallbacks[EventType::MouseButtonReleasedEvent])
                {
                    event_listener.EventCallbacks[EventType::MouseButtonReleasedEvent](event);
                }
            }
        }
        
        else if(event.IsInCategory(EventCategory::KeyEvent))
        {
            if(event.Is(EventType::KeyPressedEvent) &&
                event_listener.EventCallbacks[EventType::KeyPressedEvent])
            {
                event_listener.EventCallbacks[EventType::KeyPressedEvent](event);
            }

            else if(event.Is(EventType::KeyReleasedEvent) &&
                event_listener.EventCallbacks[EventType::KeyReleasedEvent])
            {
                event_listener.EventCallbacks[EventType::KeyReleasedEvent](event);
            }
        }
    }

};

}