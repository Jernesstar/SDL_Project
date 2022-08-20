#pragma once

#include "Event.h"
#include "Saddle/Core/MouseCodes.h"

namespace Saddle {

struct MouseMovedEvent : public Event {
    const int x, y;

    MouseMovedEvent(int x, int y)
        : Event(EventCategory::MouseEvent, EventType::MouseMovedEvent), x(x), y(y) { }
};

struct MouseScrolledEvent : public Event {
    const float DeltaScrollX; /* The amount scrolled horizontally, positive to the right and negative to the left, with float precision */
    const float DeltaScrollY; /* The amount scrolled vertically, positive away from the user and negative toward the user, with float precision */

    MouseScrolledEvent(float delta_scroll_x, float delta_scroll_y)
        : Event(EventCategory::MouseEvent, EventType::MouseScrolledEvent), 
            DeltaScrollX(delta_scroll_x), DeltaScrollY(delta_scroll_y) { }
};

struct MouseButtonEvent : public Event {
    const MouseCode MouseButton;
    const int x, y;

protected:
    MouseButtonEvent(MouseCode button, int x, int y, EventType type) 
        : Event(EventCategory::MouseEvent, type), MouseButton(button), x(x), y(y) { }
};

struct MouseButtonPressedEvent : public MouseButtonEvent {
    MouseButtonPressedEvent(MouseCode button, int x, int y)
        : MouseButtonEvent(button, x, y, EventType::MouseButtonPressedEvent) { }
};

struct MouseButtonReleasedEvent : public MouseButtonEvent {
    MouseButtonReleasedEvent(MouseCode button, int x, int y)
        : MouseButtonEvent(button, x, y, EventType::MouseButtonReleasedEvent) { }
};

}