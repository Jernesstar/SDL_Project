#pragma once

#include "Event.h"
#include "Saddle/Core/MouseCodes.h"

namespace Saddle {

struct MouseEvent : public Event {
protected:
    MouseEvent(EventType type) : Event(EventCategory::MouseEvent, type) { }
};

struct MouseMovedEvent : public MouseEvent {
    const int x, y;

    MouseMovedEvent(int x, int y)
        : MouseEvent(EventType::MouseMovedEvent), x(x), y(y) { }
};

struct MouseScrolledEvent : public MouseEvent {
    const float DeltaScrollX; /* The amount scrolled horizontally, positive to the right and negative to the left, with float precision */
    const float DeltaScrollY; /* The amount scrolled vertically, positive away from the user and negative toward the user, with float precision */

    MouseScrolledEvent(float delta_scroll_x, float delta_scroll_y)
        : MouseEvent(EventType::MouseScrolledEvent), 
            DeltaScrollX(delta_scroll_x), DeltaScrollY(delta_scroll_y) { }
};

struct MouseButtonEvent : public MouseEvent {
    const MouseCode MouseButton;
    const float x, y;

protected:
    MouseButtonEvent(EventType type, MouseCode button, float x, float y) 
        : MouseEvent(type), MouseButton(button), x(x), y(y) { }
};

struct MouseButtonPressedEvent : public MouseButtonEvent {
    MouseButtonPressedEvent(MouseCode button, int x, int y)
        : MouseButtonEvent(EventType::MouseButtonPressedEvent, button, x, y) { }
};

struct MouseButtonReleasedEvent : public MouseButtonEvent {
    MouseButtonReleasedEvent(MouseCode button, int x, int y)
        : MouseButtonEvent(EventType::MouseButtonReleasedEvent, button, x, y) { }
};

}