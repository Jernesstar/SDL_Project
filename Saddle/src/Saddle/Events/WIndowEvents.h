#pragma once

#include "Event.h"

namespace Saddle {

struct WindowEvent : public Event {
protected:
    WindowEvent(EventType type) : Event(EventCategory::WindowEvent, type) { }
};

struct WindowResizedEvent : public WindowEvent {
    const int Width, Height;

    WindowResizedEvent(int width, int height) : WindowEvent(EventType::WindowResizedEvent), Width(width), Height(height) { }
};

struct WindowClosedEvent : public WindowEvent {
    WindowClosedEvent() : WindowEvent(EventType::WindowClosedEvent) { }
};

// Note: Add more Window events

}