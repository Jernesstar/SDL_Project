#pragma once

#include <functional>

#include "Saddle/Core/UUID.h"

namespace Saddle {

template<typename TEvent>
class EventCallback {
public:
    const UUID ID;
    std::function<void(const TEvent&)> Callback;

public:
    EventCallback(const std::function<void(const TEvent&)>& callback = [](const TEvent& event) { })
        : ID(), Callback(callback) { }
        
    EventCallback<TEvent>& operator =(const EventCallback<TEvent>& other) { Callback = other.Callback; return *this; };
    EventCallback<TEvent>& operator =(const std::function<void(const TEvent&)>& callback) { Callback = callback; return *this; }

    operator bool() { return bool(this->Callback); }
    bool operator ==(const EventCallback<TEvent>& other) { return this->ID == other.ID; }
    bool operator !=(const EventCallback<TEvent>& other) { return this->ID != other.ID; }
    void operator ()(const TEvent& event) { this->Callback(event); }
};

}