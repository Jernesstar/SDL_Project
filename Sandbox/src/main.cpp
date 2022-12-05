#include <iostream>

#include <Saddle/Core/Application.h>

// #include "Demos/TextureDemo.h"
#include "Demos/Demo3D.h"

using namespace Saddle;

Application* CreateApplication(const ApplicationCommandLineArgs& args)
{
    if(std::string(args[1]) == "--project")
    {
        std::string project(args[2] ? args[2] : "Texture");
        std::cout << "Running " << project << " demo\n";

        if(project == "3D") 
            return new Demo3D();
        // if(project == "Texture")
        //     return new TextureDemo();
    }

    return nullptr;
}
