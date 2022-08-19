#pragma once

#include "Event.h"
#include "MouseCodes.h"

namespace Saddle {

struct MouseMovedEvent : public Event {
    const int x; /**< The amount scrolled horizontally, positive to the right and negative to the left, with float precision */
    const int y; /* The amount scrolled vertically, positive away from the user and negative toward the user, with float precision*/

    MouseMovedEvent(int x, int y)
        : Event(EventCategory::MouseEvent, EventType::MouseMovedEvent), x(x), y(y) { }
};

struct MouseScrolledEvent : public Event {
    const float OffsetX, OffsetY;

    MouseScrolledEvent(float offset_x, float offset_y)
        : Event(EventCategory::MouseEvent, EventType::MouseScrolledEvent), OffsetX(offset_x), OffsetY(offset_y) { }
};

struct MouseButtonEvent : public Event {
    const MouseCode MouseButton;

protected:
    MouseButtonEvent(MouseCode button, EventType type) 
        : Event(EventCategory::MouseEvent, type), MouseButton(button) { }
};

struct MouseButtonPressedEvent : public MouseButtonEvent {
    MouseButtonPressedEvent(MouseCode button)
        : MouseButtonEvent(button, EventType::MouseButtonPressedEvent) { }
};

struct MouseButtonReleasedEvent : public MouseButtonEvent {
    MouseButtonReleasedEvent(MouseCode button)
        : MouseButtonEvent(button, EventType::MouseButtonReleasedEvent) { }
};

}