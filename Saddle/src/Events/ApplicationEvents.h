#pragma once

#include "Event.h"

namespace Saddle {

class ApplicationEvent : public Event {
protected:
    ApplicationEvent(EventType type) : Event(EventCategory::ApplicationEvent, type) { }
};

class WindowResizedEvent : public ApplicationEvent {
public:
    const int Width, Height;

public:
    WindowResizedEvent(int width, int height) : ApplicationEvent(EventType::WindowResizedEvent), Width(width), Height(height) { }
};

class WindowClosedEvent : public ApplicationEvent {
public:
    WindowClosedEvent() : ApplicationEvent(EventType::WindowClosedEvent) { }
};

// Note: Add more Window events

}