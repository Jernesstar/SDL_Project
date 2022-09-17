#include <Saddle/Core/Application.h>

using namespace Saddle;

class App : public Application {
public:
    void Run() override
    {
        while(!glfwWindowShouldClose(m_Window.GetNativeWindow()))
        {

        }
    }
};

int main()
{
    Application::Init();

    App app;
    app.Run();

    Application::Close();
}
