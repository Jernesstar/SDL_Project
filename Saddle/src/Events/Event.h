#pragma once

namespace Saddle {

enum class EventCategory {
    MouseEvent,
    KeyEvent,
    ApplicationEvent
};

enum class EventType {
    KeyPressedEvent,
    KeyReleasedEvent,
    MouseMovedEvent,
    MouseScrolledEvent,
    MouseButtonPressedEvent,
    MouseButtonReleasedEvent,
};

struct Event {
    const EventCategory Category;
    const EventType Type;
    bool Handled = false;

    bool IsInCategory(EventCategory category)
    {
        return this->Category == category;
    }
    
    bool Is(EventType type)
    {
        return this->Type == type;
    }

protected:
    Event(EventCategory category, EventType type) : Category(category), Type(type) { }
};

}