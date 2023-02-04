#pragma once

#include <functional>

#include "Saddle/Core/UUID.h"

namespace Saddle {

template<typename TEvent>
class EventCallback {
public:
    EventCallback(const std::function<void(const TEvent&)>& callback = [](const TEvent& event) { })
        : m_ID(), m_Callback(callback) { }
        
    EventCallback<TEvent>& operator =(const EventCallback<TEvent>& other) = default;
    EventCallback<TEvent>& operator =(const std::function<void(const TEvent&)>& callback) { m_Callback = callback; return *this; }

    operator bool() const { return bool(this->m_Callback); }
    bool operator ==(const EventCallback<TEvent>& other) const { return this->m_ID == other.m_ID; }
    bool operator !=(const EventCallback<TEvent>& other) const { return this->m_ID != other.m_ID; }
    void operator ()(const TEvent& event) const { this->m_Callback(event); }

    const UUID& GetID() const { return m_ID; }
    const std::function<void(const TEvent&)> GetCallback() const { return m_Callback; } 

private:
    UUID m_ID;
    std::function<void(const TEvent&)> m_Callback;
};

}