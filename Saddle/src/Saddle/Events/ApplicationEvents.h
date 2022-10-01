#pragma once

#include "Event.h"

namespace Saddle {

struct ApplicationEvent : public Event {
protected:
    ApplicationEvent(EventType type) : Event(EventCategory::Application, type) { }
};

// Note: Have some Application events

}