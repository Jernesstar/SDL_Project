#pragma once

#include "Event.h"
#include "MouseCodes.h"

namespace Saddle {

struct MouseMovedEvent : public Event {
    const float x, y;

    MouseMovedEvent(float x, float y)
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