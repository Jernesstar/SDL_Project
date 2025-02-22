#pragma once

namespace Saddle {

enum class EventCategory {
    Key,
    Mouse,
    Window,
    Application,
};

enum class EventType {
    KeyPressed,
    KeyReleased,
    KeyCharEvent,
    MouseMoved,
    MouseScrolled,
    MouseButtonPressed,
    MouseButtonReleased,
    WindowResized,
    WindowMoved,
    WindowClosed,
    ApplicationUpdated
};

struct Event {
    const EventCategory Category;
    const EventType Type;
    bool Handled = false;

    bool IsInCategory(EventCategory category) const { return this->Category == category; }
    bool Is(EventType type) const { return this->Type == type; }

    template<typename TEvent>
    TEvent& As() const { return *((TEvent*)(this)); }

protected:
    Event(EventCategory category, EventType type) : Category(category), Type(type) { }
};

}