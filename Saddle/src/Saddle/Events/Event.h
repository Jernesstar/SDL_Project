#pragma once

namespace Saddle {

enum EventCategory {
    MouseEvent       = 0x0001,
    KeyEvent         = 0x0010,
    ApplicationEvent = 0x0100
};

enum class EventType {
    KeyPressedEvent,
    KeyReleasedEvent,
    MouseMovedEvent,
    MouseScrolledEvent,
    MouseButtonPressedEvent,
    MouseButtonReleasedEvent,
    WindowResizedEvent,
    WindowClosedEvent,
    ApplicationClosedEvent
};

struct Event {
    const EventCategory Category;
    const EventType Type;
    bool Handled = false;

    bool IsInCategory(EventCategory category) { return this->Category & category; }
    bool Is(EventType type) { return this->Type == type; }

    template<typename TEvent>
    TEvent& CastAs() { return *((TEvent*)(this)); }
    
protected:
    Event(EventCategory category, EventType type) : Category(category), Type(type) { }
};

}