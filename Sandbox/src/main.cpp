#include <iostream>

#include <Saddle/Core/Application.h>

#include "Demos/TextureDemo.h"
#include "Demos/FontDemo.h"
#include "Demos/3DCube.h"
#include "Snake/Game.h"

using namespace Saddle;

Application* CreateApplication(const ApplicationCommandLineArgs& args)
{
    if(std::string(args[1]) == "--project")
    {
        std::string project(args[2] ? args[2] : "Texture");
        std::cout << "Running " << project << " demo\n";

        if(project == "Cube") 
            return new Cube3D();
        if(project == "Texture")
            return new TextureDemo();
        if(project == "Font")
            return new FontDemo();
        if(project == "Game")
            return new Game(1000, 600);
    }

    return new Cube3D();
}
