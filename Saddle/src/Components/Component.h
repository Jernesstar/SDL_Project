#pragma once

namespace Saddle {

class IComponent {

public:
    virtual void OnUpdate() = 0;

protected:
    IComponent();
    virtual ~IComponent() = default;

};

}