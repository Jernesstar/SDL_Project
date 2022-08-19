#pragma once

#include "Event.h"
#include "Saddle/Core/KeyCodes.h"

namespace Saddle {

class KeyEvent : public Event {
public:
    const KeyCode Key;

protected:
    KeyEvent(KeyCode key, EventType type) : Event(EventCategory::KeyEvent, type), Key(key) { }
};

class KeyPressedEvent : public KeyEvent {
public:
    bool IsRepeat = false;
    
public:
    KeyPressedEvent(KeyCode key) : KeyEvent(key, EventType::KeyPressedEvent) { }
};

class KeyReleasedEvent : public KeyEvent {
public:
    KeyReleasedEvent(KeyCode key) : KeyEvent(key, EventType::KeyReleasedEvent) { }
};

}