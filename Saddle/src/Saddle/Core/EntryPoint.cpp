#include "Application.h"

using namespace Saddle;

// Will need to be defined by client
extern Application* CreateApplication(const ApplicationCommandLineArgs& args);

int main(int argc, char** argv)
{
    Application::Init({ argc, argv });

    Application* app = CreateApplication({ argc, argv });
    app->Run();

    Application::Close();
}