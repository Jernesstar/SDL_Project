#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <Saddle/Core/Application.h>

using namespace Saddle;

struct Vertex {
    glm::vec2 Position;
    glm::vec2 TextureCoordinate;
};

class App : public Application {
public:
    App()
    {
        Window.SetWindowIcon("Sandbox/assets/images/start_bg.png");
    }
    void Run() override;
};

Application* CreateApplication() { return new App(); }
