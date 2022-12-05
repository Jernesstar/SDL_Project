#pragma once

#include "Event.h"
#include "Saddle/Core/Time.h"

namespace Saddle {

struct ApplicationEvent : public Event {
protected:
    ApplicationEvent(EventType type) : Event(EventCategory::Application, type) { }
};

struct ApplicationUpdatedEvent : public ApplicationEvent {
    TimeStep DeltaTime;

    ApplicationUpdatedEvent(TimeStep ts) : ApplicationEvent(EventType::ApplicationUpdated), DeltaTime(ts) { }
};

}