#include "Event.h"
#include "KeyCodes.h"

namespace Saddle {

class KeyEvent : public Event {

public:
    const Saddle::Key Key;

protected:
    KeyEvent(Saddle::Key key, EventType type) : Event(type), Key(key) { }
};

class KeyPressedEvent : public KeyEvent {

public:
    bool IsRepeat = false;
    
public:
    KeyPressedEvent(Saddle::Key key) : KeyEvent(key, EventType::KeyPressedEvent) { }
};

class KeyReleasedEvent : public KeyEvent {

public:
    KeyReleasedEvent(Saddle::Key key) : KeyEvent(key, EventType::KeyReleasedEvent) { }
};

}