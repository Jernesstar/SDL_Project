#include "Application.h"

using namespace Saddle;

extern Application* CreateApplication(); // Will need to be defined by client

int main()
{
    Application::Init();

    Application* app = CreateApplication();
    app->Run();

    Application::Close();
}