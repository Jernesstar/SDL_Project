#pragma once

#include "Event.h"
#include "Saddle/Core/KeyCodes.h"

namespace Saddle {

struct KeyEvent : public Event {
    const KeyCode Key;

protected:
    KeyEvent(KeyCode key, EventType type) : Event(EventCategory::KeyEvent, type), Key(key) { }
};

struct KeyPressedEvent : public KeyEvent {
    bool IsRepeat = false;
    
    KeyPressedEvent(KeyCode key) : KeyEvent(key, EventType::KeyPressedEvent) { }
};

struct KeyReleasedEvent : public KeyEvent {
    KeyReleasedEvent(KeyCode key) : KeyEvent(key, EventType::KeyReleasedEvent) { }
};

}