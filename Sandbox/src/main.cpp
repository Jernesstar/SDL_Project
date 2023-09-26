#include <iostream>

#include <Saddle/Core/Application.h>

#include "Demos/CubeDemo.h"
#include "Demos/FontDemo.h"
#include "Demos/LightingDemo.h"
#include "Demos/ModelDemo.h"
#include "Demos/TextureDemo.h"
#include "Snake/Game.h"

using namespace Saddle;

Application* CreateApplication(const ApplicationCommandLineArgs& args)
{
    if(std::string(args[1]) == "--project")
    {
        std::string project(args[2] ? args[2] : "Cube");
        std::cout << "Running " << project << " demo\n";

        if(project == "Cube") 
            return new CubeDemo();
        if(project == "Font")
            return new FontDemo();
        if(project == "Lighting")
            return new LightingDemo();
        if(project == "Model")
            return new ModelDemo();
        if(project == "Texture")
            return new TextureDemo();
        if(project == "Snake")
            return new Game(1000, 600);
    }

    return new CubeDemo();
}
