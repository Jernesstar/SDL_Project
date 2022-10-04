#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <Saddle/Core/Application.h>

using namespace Saddle;

struct Vertex {
    glm::vec2 Position;
    glm::vec4 Color;
};

class App : public Application {
public:
    void Run() override;
};

Application* CreateApplication() { return new App(); }
