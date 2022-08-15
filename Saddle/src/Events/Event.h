#pragma once

namespace Saddle {

enum class EventType {
    KeyPressedEvent,
    KeyReleasedEvent,
    MouseMovedEvent,
    MouseScrolledEvent,
    MouseButtonPressedEvent,
    MouseButtonReleasedEvent,
};

struct Event {
    const EventType Type;
    bool Handled = false;

    bool Is(EventType type)
    {
        return this->Type == type;
    }

protected:
    Event(EventType type) : Type(type) { }
};

}