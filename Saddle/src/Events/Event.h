#pragma once

namespace Saddle {

enum class EventType {
    KeyPressedEvent,
    KeyReleasedEvent
};

class Event {

public:
    const EventType Type;
    bool Handled = false;

public:
    Event(EventType type) : Type(type) { }
    virtual ~Event() = default;
};

}