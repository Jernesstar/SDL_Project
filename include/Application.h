#pragma once

#include "Window.h"

namespace Saddle {

class Application {

public:


public:
    static void Init();

private:
    inline static Application* instance;
    Saddle::Window window;
    
private:
    Application();
    ~Application();
};
    
}
