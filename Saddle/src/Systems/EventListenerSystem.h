#include "Components.h"
#include "Entity.h"

namespace Saddle {

class EventListenerSystem {

public:
    static void OnEvent(Entity& entity, SDL_Event& event)
    {
        Coordinate2DComponent& coordinate = entity.GetComponent<Coordinate2DComponent>();
        RectComponent& rect = entity.GetComponent<RectComponent>();
        EventListenerComponent& event_listener = entity.GetComponent<EventListenerComponent>();

        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            int mouse_x = event.button.x;
            int mouse_y = event.button.y;
            bool x_coord_is_in_bound = coordinate.x <= mouse_x && mouse_x <= coordinate.x + rect.width;
            bool y_coord_is_in_bound = coordinate.y <= mouse_y && mouse_y <= coordinate.y + rect.width;

            if(x_coord_is_in_bound && y_coord_is_in_bound)
            {
                if(event_listener.OnEventClick)
                    event_listener.OnEventClick(event);
            }
        }

        else if(event.type == SDL_KEYDOWN)
        {
            if(event_listener.OnEventKeyPress)
                event_listener.OnEventKeyPress(event);
        }
    }

};

}