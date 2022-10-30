#pragma once

#include "Event.h"
#include "Saddle/Core/MouseCodes.h"

namespace Saddle {

struct MouseEvent : public Event {
protected:
    MouseEvent(EventType type) : Event(EventCategory::Mouse, type) { }
};

struct MouseMovedEvent : public MouseEvent {
    const float x, y;

    MouseMovedEvent(float x, float y)
        : MouseEvent(EventType::MouseMoved), x(x), y(y) { }
};

struct MouseScrolledEvent : public MouseEvent {
    const float ScrollX; /* The amount scrolled horizontally, positive to the right and negative to the left, with float precision */
    const float ScrollY; /* The amount scrolled vertically, positive away from the user and negative toward the user, with float precision */

    MouseScrolledEvent(float scroll_x, float scroll_y)
        : MouseEvent(EventType::MouseScrolled), 
            ScrollX(scroll_x), ScrollY(scroll_y) { }
};

struct MouseButtonEvent : public MouseEvent {
    const MouseCode MouseButton;
    const float x, y;

protected:
    MouseButtonEvent(EventType type, MouseCode button, float x, float y) 
        : MouseEvent(type), MouseButton(button), x(x), y(y) { }
};

struct MouseButtonPressedEvent : public MouseButtonEvent {
    MouseButtonPressedEvent(MouseCode button, float x, float y)
        : MouseButtonEvent(EventType::MouseButtonPressed, button, x, y) { }
};

struct MouseButtonReleasedEvent : public MouseButtonEvent {
    MouseButtonReleasedEvent(MouseCode button, float x, float y)
        : MouseButtonEvent(EventType::MouseButtonReleased, button, x, y) { }
};

}